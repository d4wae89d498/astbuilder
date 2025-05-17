#ifndef GRAMMAR_NODE_ALT_H
# define GRAMMAR_NODE_ALT_H
# include "./../Grammar.h"
# define _alt(arr) AltNode_new(arr, sizeof(arr) / sizeof(arr[0]))
# define alt(...) _alt(((GrammarNode*[]) { __VA_ARGS__ }))

typedef struct s_AltNode {
    GrammarNode base;
    GrammarNode **nodes;
    size_t size;
} AltNode;

Ast* AltNode_match(GrammarNode *this, struct s_Ctx *ctx)
{
    AltNode     *self;
    AltNode     *output;
    size_t      i;

    self = (AltNode*) this;

    i = 0;
    while (i < self->size)
    {
        Ast *output = GrammarNode_match(self->nodes[i], ctx);
        if (output)
            return output;
        i += 1;   
    }
    return NULL;
}

void AltNode_delete(GrammarNode *this)
{
    AltNode     *self;
    size_t      i;

    if (!this)
        return;
    self = (AltNode*) this;
    i = 0;
    while (i < self->size)
    {
        GrammarNode_delete(self->nodes[i]);
        i += 1;
    }
}

GrammarNode *AltNode_new(GrammarNode **nodes, size_t size)
{
    AltNode     *output;

    output = malloc(sizeof(AltNode));
    output->nodes = nodes;
    output->size = size;
    output->base.Match = AltNode_match;
    output->base.Delete = AltNode_delete;
    return (GrammarNode*) output;
}

#endif