#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "bst.h"
#include "heap.h"
#include "evaluation.h"

// file-wide state

static Tree *vars;
static Heap *vals;
static char temp[200];

static char *strip(char *str) {
    // strip right
    int i = strlen(str) - 1;
    for (; isspace(str[i]); --i);
    str[i+1] = 0;
    // strip left
    while (isspace(*str))
        str++;

    return str;
}

void substitute(Tree *root, const char *exp, char *dest) { // preorder tree traversal
    if (!root)
        return;

    char *jmp = dest;
    size_t len = strlen(root->value.var);
    while ((jmp = strstr(jmp, root->value.var))) { // substitute all occurrences
        strcpy(temp, &jmp[len]); // bureaucracy
        sprintf(&dest[jmp-dest], "%f%s", root->value.val, temp);
        jmp = dest;
    } // check

    substitute(root->left, exp, dest);
    substitute(root->right, exp, dest);
}

static void err(void) {
    puts("Error in expression.");
    exit(1);
}

Variable evaluateLine(char *line) { // format: LHS is var identifier, RHS is infix expression
    Variable variable;
    Variable *send = NULL;
    char new[200];

    // step 1: tokenize
    strcpy(variable.var, strip(strtok(line, "=")));
    char *exp = strip(strtok(0, "="));

    if (!exp)
        err();

    // step 2: substitute available vars
    if (vars) {
        strcpy(new, exp);
        substitute(vars, exp, new);
    }

    // step 3: infixToPostfix then evaluate
    if (vars)
        infixToPostfix(new, temp, 200);
    else
        infixToPostfix(exp, temp, 200);

    variable.val = evaluatePostfix(temp);

    // step 4: add to symbols
    Tree *node;
    if ((node = searchTree(vars, variable.var))) // already there
        node->value.val = variable.val;
    else
        vars = insertLeaf(vars, variable, &send);

    // step 5: check for valid LHS
    strcpy(new, variable.var);
    substitute(vars, variable.var, new);
    infixToPostfix(new, temp, 200);
    if (strcmp(new, temp))
        err();

    if (send)
        insertToHeap(vals, send);

    return variable;
}

void inOrder(Tree *root) {
    if (!root)
        return;

    inOrder(root->left);
    printf("%s = %f\n", root->value.var, root->value.val);
    inOrder(root->right);
}

int main(void) {
    vars = NULL;
    vals = initHeap(20);

    FILE *src = fopen("src.txt", "r");
    char line[200];
    Variable var;

    printf("\tVariables as Initial Input\n");
    while (fgets(line, 200, src)) {
        var = evaluateLine(line);
        printf("%s = %f\n", var.var, var.val);
    }

    printf("\tVariables Sorted Alphabetically\n");
    inOrder(vars);

    printf("\tVariables Sorted Numerically in Ascending Order\n");
    Variable *v;
    while ((v = popMin(vals)))
        printf("%s = %f\n", v->var, v->val);

    return 0;
}
