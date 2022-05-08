#include <stdlib.h>
#include "stack.h"

struct stack {
    Object *arr; // using a primitive struct to ensure passing copies for the stack
    size_t top, capacity;
};

Stack *stack_initialize(size_t c) {
    Stack *s = malloc(sizeof(Stack));
    s->arr = malloc(sizeof(Object) * c);
    s->top = 0;
    s->capacity = c;
    return s;
}

Object pop(Stack *s) {
    stack_errno = s->top > 0 ? 0 : 2;
    return (stack_errno ? (Object) {} : s->arr[--s->top]);
}

void push(Stack *s, Object e) {
    stack_errno = s->top == s->capacity;
    if (!stack_errno) s->arr[s->top++] = e;
}

Object top(Stack *s) {
    stack_errno = s->top > 0 ? 0 : 2;
    return (stack_errno ? (Object) {} : s->arr[s->top-1]);
}

int stack_isEmpty(Stack *s) {
    return !s->top;
}
