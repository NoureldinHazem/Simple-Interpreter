// #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bst.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

Tree *newTree(Variable variable) {
    Tree *node = malloc(sizeof(Tree));
    node->value = variable;
    node->left = NULL;
    node->right = NULL;

    return node;
}

Tree *insertLeaf(Tree *root, Variable value, Variable **new) {
    if (!root) {
        Tree *t = newTree(value);
        *new = &t->value;
        return t;
    }

    int v = strcmp(value.var, root->value.var);
    if (v < 0)
        root->left = insertLeaf(root->left, value, new);
    else if (v > 0)
        root->right = insertLeaf(root->right, value, new);

    return root; // default if duplicate
}

Tree *searchTree(Tree *root, char *var) {
    if (!root) // dead end
        return NULL;

    int v = strcmp(var, root->value.var);
    if (v < 0)
        return searchTree(root->left, var);
    if (v > 0)
        return searchTree(root->right, var);

    return root; // found
}

size_t treeSize(Tree *root) {
    if (!root)
        return 0;

    return 1 + treeSize(root->left) + treeSize(root->right);
}

int treeHeight(Tree *root) {

    if (!root)
        return -1; // empty tree

    int left = treeHeight(root->left);
    int right = treeHeight(root->right);

    return 1 + MAX(left, right);
}

Tree *findMin(Tree *root) {
    if (!root)
        return NULL;

    if (root->left)
        return findMin(root->left);

    return root;
}

Tree *findMax(Tree *root) {
    if (!root)
        return NULL;

    if (root->right)
        return findMax(root->right);

    return root;
}

// void delete(Tree *root, char var) { // deletes and replaces a node
//     Tree *parent;
//     Tree *node = searchTree(root, var);
//     Tree *replacement;
//
//     if (!!node->left + !!node->right == 2) {
//         // case 1: two children
//         replacement = findMin(node->right);
//         Variable tmp = replacement->value;
//         delete(node, tmp.var); // delete min leaf
//         node->value = tmp; // data exchange
//     } else {
//         // case 2: one or zero children
//         replacement = node->left ? node->left : node->right;
//         free(node);
//
//         if (parent->left == node)
//             parent->left = replacement;
//         else if (parent->right == node)
//             parent->right = replacement;
//     }
// }

/*
    // Usage example

int main(void) {
    int arr[] = {16,64,85,45,4,93,26,52,22,63};
    Tree *root = NULL;

    for (int i = 0; i < 10; ++i)
        root = insertLeaf(root, arr[i]);

    delete(root, 16);
    delete(root, 64);

    printf("Tree Size = %lu\n", treeSize(root));
    printf("Tree Height = %d\n", treeHeight(root));
    printf("PreOrder: "); preOrder(root); printf("\n");
    printf("InOrder: "); inOrder(root); printf("\n");
    printf("PostOrder: "); postOrder(root); printf("\n");

    printf("Min: %d\n", findMin(root)->value);
    printf("Max: %d\n", findMax(root)->value);

    return 0;
}

*/
