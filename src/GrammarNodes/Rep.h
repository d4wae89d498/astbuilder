#ifndef GRAMMAR_NODE_REP_H
# define GRAMMAR_NODE_REP_H
# include "./../Grammar.h"
# define rep(A) RepNode_new(A)

typedef struct s_RepNode {
    GrammarNode base;
    GrammarNode *A;
} RepNode;

Ast* RepNode_match(GrammarNode *this, struct s_Ctx *ctx)
{
    RepNode *self = (RepNode*) this;

    Ast *output;
    Ast *next;
  //  output = Ast

    if (!(output = GrammarNode_match(self->A, ctx)))
        return (NULL);
    Ctx_next(ctx);
    while ((next = GrammarNode_match(self->A, ctx)))
    {
        Ast_add(&output, next);
        Ctx_next(ctx);
    }
    return output;//(true);
}

void RepNode_delete(GrammarNode *this)
{
    RepNode *self = (RepNode*) this;

    GrammarNode_delete(self->A);
}

GrammarNode *RepNode_new(GrammarNode *A)
{
    RepNode  *output;

    output = malloc(sizeof(RepNode));
    output->A = A;
    output->base.Match = RepNode_match;
    output->base.Delete = RepNode_delete;
    return (GrammarNode*) output;
}

#endif