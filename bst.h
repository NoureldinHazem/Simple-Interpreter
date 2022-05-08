#ifndef BST_H
#define BST_H

#include "varstruct.h"

typedef struct Tree {
    Variable value;

    struct Tree *left, *right;
} Tree;

// interface prototypes
Tree *newTree(Variable variable);
Tree *insertLeaf(Tree *root, Variable value, Variable **new);
Tree *searchTree(Tree *root, char *var);
Tree *findMin(Tree *root);
Tree *findMax(Tree *root);
// void delete(Tree *root, char *var);
// query functions
size_t treeSize(Tree *root);
int treeHeight(Tree *root);

#endif
