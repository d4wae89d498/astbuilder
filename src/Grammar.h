#ifndef GRAMMAR_NODE_H
# define GRAMMAR_NODE_H
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>

# include "Ast.h"

# define gdef(g, name, node) Grammar_add_rule(g, #name, node)
# define term_prop(g, prec, name, asso) Grammar_add_term(g, name, prec, asso)
# define MAX_RULES_COUNT   255
# define MAX_TERMS_COUNT     64

typedef struct s_Ctx Ctx;
typedef struct s_CtxBackup CtxBackup;

void        Ctx_next(Ctx*);
CtxBackup   *CtxBackup_new(Ctx *);
CtxBackup   *CtxBackup_restore(CtxBackup*, Ctx *);
CtxBackup   *CtxBackup_delete(CtxBackup *);


typedef struct s_GrammarNode
{
    char            *name;
    Ast*            (*Match)(struct s_GrammarNode *, struct s_Ctx *);
    void            (*Delete)(struct s_GrammarNode *);
}   GrammarNode;

Ast     *GrammarNode_match(struct s_GrammarNode *this, struct s_Ctx *ctx)
{
    return this->Match(this, ctx);
}

void    GrammarNode_delete(struct s_GrammarNode *this)
{
    if (this)
    {
        this->Delete(this);
        free(this);
    }
}

typedef struct s_GrammarRule 
{
    char            *name; 
    GrammarNode     *def;
} GrammarRule;

typedef struct s_TermProp
{
    char            *name;
    unsigned        precedence;
    enum { ASSO_LEFT, ASSO_RIGHT, ASSO_NONE }    
                    associativity;
}   TermProp;

typedef struct s_Grammar
{
    GrammarRule     rules[MAX_RULES_COUNT];
    unsigned        rules_count;

    TermProp        terms[MAX_TERMS_COUNT];
    unsigned        terms_count;
} Grammar;

void    Grammar_add_rule(Grammar *self, char *name, GrammarNode *def)
{
    if (self->rules_count >= MAX_RULES_COUNT) 
    {
        fprintf(stderr, "Error, too many rules defined.\n");
        exit(0);
    }
    self->rules[self->rules_count++] = (GrammarRule) { .name = name, .def = def };
}

void    Grammar_add_term(Grammar *self, char *name, unsigned prec, int asso)
{
    if (self->terms_count >= MAX_TERMS_COUNT) 
    {
        fprintf(stderr, "Error, too many terms defined.\n");
        exit(0);
    }
    self->terms[self->terms_count++] = (TermProp) { .name = name, .precedence = prec, .associativity = asso };
}

#endif