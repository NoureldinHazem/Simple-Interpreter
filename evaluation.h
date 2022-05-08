#ifndef EVALUATION_H
#define EVALUATION_H

void infixToPostfix(char *infix, char *postfix, size_t n);
double evaluatePostfix(const char *postfix);

#endif
