#ifndef GRAMMAR_NODE_OPT_H
# define GRAMMAR_NODE_OPT_H
# include "./../Grammar.h"
# define opt(A) OptNode_new(A)

typedef struct s_OptNode {
    GrammarNode base;
    GrammarNode *A;
} OptNode;

Ast* OptNode_match(GrammarNode *this, struct s_Ctx *ctx)
{
    OptNode *self = (OptNode*) this;
    Ast *output = GrammarNode_match(self->A, ctx);
    if (output)
        return output;
    return Ast_new((Ast) {.type="ignore", .value=NULL, .child=NULL, .next = NULL});
}

void OptNode_delete(GrammarNode *this)
{
    OptNode *self = (OptNode*) this;

    GrammarNode_delete(self->A);
}

GrammarNode *OptNode_new(GrammarNode *A)
{
    OptNode  *output;

    output = malloc(sizeof(OptNode));
    output->A = A;
    output->base.Match = OptNode_match;
    output->base.Delete = OptNode_delete;
    return (GrammarNode*) output;
}

#endif