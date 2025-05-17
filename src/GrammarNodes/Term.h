#ifndef TERM_NODE_H
# define TERM_NODE_H

#include "../Grammar.h"
#include "../Ctx.h"
#include <string.h>

#define term(A) TermNode_new(A)

typedef struct s_TermNode {
    GrammarNode base;
    char *value;
} TermNode;

Ast* TermNode_match(GrammarNode *node, Ctx *ctx)
{
    TermNode *self = (TermNode*)node;
    size_t len = strlen(self->value);
    
    printf("%s\n", self->value);

    if (strlen(ctx->source + ctx->position) < len) {
        return NULL;
    }
    
    if (strncmp(ctx->source + ctx->position, self->value, len) == 0) {
        ctx->position += len;
        return Ast_new((Ast){
            .type = "term",
            .value = self->value,
            .child = NULL,
            .next = NULL
        });
    }
    
    return NULL;
}

void TermNode_delete(GrammarNode *this)
{

}

GrammarNode *TermNode_new(char *value)
{
    TermNode *node = (TermNode*)malloc(sizeof(TermNode));
    if (!node) return NULL;
    
    node->base.name = "term";
    node->base.Match = TermNode_match;
    node->base.Delete = TermNode_delete;
    node->value = value;
    
    return (GrammarNode*)node;
}

#endif