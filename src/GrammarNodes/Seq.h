#ifndef GRAMMAR_NODE_SEQ_H
# define GRAMMAR_NODE_SEQ_H
# include "./../Grammar.h"
# define _seq(arr) SeqNode_new(arr, sizeof(arr) / sizeof(arr[0]))
# define seq(...) _seq(((GrammarNode*[]) { __VA_ARGS__ }))

typedef struct s_SeqNode {
    GrammarNode base;
    GrammarNode **nodes;
    size_t size;
} SeqNode;

Ast *SeqNode_match(GrammarNode *this, struct s_Ctx *ctx)
{
    SeqNode *self = (SeqNode*) this;
    
    size_t i = 0;
    Ast *output = NULL;
    while (i < self->size)
    {
        Ast *node;
        if (!(node = GrammarNode_match(self->nodes[i], ctx)))
        {
            Ast_delete(output);
            return NULL;
        }
        Ast_add(&output, node);
        i += 1;
    }
    return output;
}

void SeqNode_delete(GrammarNode *this)
{
    SeqNode *self = (SeqNode*) this;
    size_t i = 0;
    while (i < self->size)
        GrammarNode_delete(self->nodes[i++]);
}

GrammarNode *SeqNode_new(GrammarNode **nodes, size_t size)
{
    SeqNode  *output;

    output = malloc(sizeof(SeqNode));
    output->nodes = nodes;
    output->size = size;
    output->base.Match = SeqNode_match;
    output->base.Delete = SeqNode_delete;
    return (GrammarNode*) output;
}

#endif