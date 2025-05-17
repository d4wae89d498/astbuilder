#ifndef RULE_NODE_H
# define RULE_NODE_H

#include "../Grammar.h"
#include "../Ctx.h"
#include <string.h>
#define rule(A) RuleNode_new(#A)

typedef struct s_RuleNode {
    GrammarNode base;
    char *rule_name;
} RuleNode;

Ast*  RuleNode_match(GrammarNode *node, Ctx *ctx)
{
    RuleNode *self = (RuleNode*)node;
    
    // Find the referenced rule
    for (unsigned i = 0; i < ctx->y.rules_count; i++) {
        if (strcmp(ctx->y.rules[i].name, self->rule_name) == 0) {
            if (!strcmp(ctx->last_rule, node->name))
            {
                fprintf(stderr, "Infinite loop detected in grammar.\n");
                exit(0);
            }
            ctx->last_rule = node->name;
            return ctx->y.rules[i].def->Match(ctx->y.rules[i].def, ctx);
        }
    }
    return NULL;
}

void RuleNode_delete(GrammarNode *this)
{

}

GrammarNode *RuleNode_new(char *rule_name)
{
    RuleNode *node = (RuleNode*)malloc(sizeof(RuleNode));
    if (!node) return NULL;
    
    node->base.name = "rule";
    node->base.Match = RuleNode_match;
    node->base.Delete = RuleNode_delete;
    node->rule_name = rule_name;
    
    return (GrammarNode*)node;
}

#endif