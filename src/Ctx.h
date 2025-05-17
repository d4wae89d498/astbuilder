#ifndef CONTEXT_H
# define CONTEXT_H
# include "Ast.h"
# include "Grammar.h"
# include <string.h>
# include <stdio.h>

typedef struct s_Ctx
{
    char    *source;       // Current position in source text
    size_t  position;      // Current position as offset
    Ast     *ast;          // Abstract Syntax Tree
    Grammar y;             // Grammar definition
    char    *last_rule;    // Used to detect infinite reccursion
    char    *grammar_rule; // Used to create a 
} Ctx;

struct s_CtxBackup 
{
    size_t  position;      // Saved position in source
};

//////////////////////////////////////////////////////

void Ctx_next(Ctx *ctx)
{
    if (ctx->source[ctx->position] != '\0') {
        ctx->position += 1;
    }
}

CtxBackup *CtxBackup_new(Ctx *ctx)
{
    CtxBackup *bkp = (CtxBackup*)malloc(sizeof(CtxBackup));
    if (!bkp) return NULL;
    
    bkp->position = ctx->position;
    return bkp;
}

CtxBackup *CtxBackup_restore(CtxBackup *bkp, Ctx *ctx)
{
    if (!bkp) return NULL;
    
    ctx->position = bkp->position;
    return bkp;
}

CtxBackup *CtxBackup_delete(CtxBackup *bkp)
{
    free(bkp);
    return NULL;
}

//////////////////////////////////////////////////////

Ast* try_rule(Ctx *self, unsigned i)
{
    CtxBackup *bkp = CtxBackup_new(self);
    if (!bkp) return false;

    printf("[trying rule %s...]\n", self->y.rules[i].name);
    self->grammar_rule = self->y.rules[i].name;
    size_t  begin = self->position;
    Ast *output = self->y.rules[i].def->Match(self->y.rules[i].def, self);
    if (output)
    {
        Ast *what = Ast_new((Ast) {.type=self->y.rules[i].name, .value=NULL,.next=NULL,.child=output});
        return what;
    }
    return NULL;
}

void cmatch(Ctx *self)
{
    size_t last_pos = (size_t)-1;
    
    while (self->source[self->position])
    {
        unsigned i = 0;
        bool matched = false;
        size_t start_pos = self->position;

        Ast     *longest_match_node;
        size_t  longest_position = 0;
        size_t  position = self->position;

        while (i < self->y.rules_count)
        {
            Ast *candidate_node = NULL;
            if ((candidate_node = try_rule(self, i)) && self->position > longest_position) {
                longest_position = self->position;
                longest_match_node = candidate_node;
            }
            self->position = position;
            i += 1;
        }

        if (!longest_match_node) {   
            printf("syntax error: no matching rule found at %zu.\n", self->position);
            break ;
        } 
        Ast_add(&(self->ast), longest_match_node);
        self->position = longest_position;

        printf("->[pos: %zu]\n", self->position);
    }

    if (!self->source[self->position]) {
        printf("match end\n");
    }
}

#endif