#ifndef AST_H
# define AST_H

typedef struct s_Ast
{
    char            *type;
    char            *value;
    struct s_Ast    *next;
    struct s_Ast    *child;    
} Ast;

Ast *Ast_new(Ast ast)
{
    Ast *node = malloc(sizeof(Ast));
    *node = ast;
    return node;
}

void Ast_add(Ast **root, Ast *node)
{
    if (*root == NULL)
    {
        *root = node;
        return;
    }

    Ast *current = *root;
    while (current->next)
        current = current->next;

    current->next = node;
}

void Ast_delete(Ast *this)
{
    if (!this)
        return;
    // TODO: check if we need to free value/type 
    Ast_delete(this->next);
    Ast_delete(this->child);
    free(this);
}

void _Ast_dump(const Ast *node, int depth)
{
    if (!node)
        return;

    for (int i = 0; i < depth; ++i)
        printf("  "); // Indentation

    if (node->value)
        printf("- %s (%s)\n", node->type, node->value);
    else 
        printf("- %s \n", node->type);

    // Recursively dump child
    if (node->child)
        _Ast_dump((Ast *)node->child, depth + 1);

    // Dump next sibling
    if (node->next)
        _Ast_dump((Ast *)node->next, depth);
}

void Ast_dump(const Ast *root)
{
    printf("AST Dump:\n");
    _Ast_dump(root, 0);
}

#endif