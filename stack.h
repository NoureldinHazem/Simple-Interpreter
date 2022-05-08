#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef struct stack Stack;
typedef union {
    void *pointer;
    int integer;
    double d;
} Object;

static int stack_errno; // 0 for success on push/pop/top, 1 for full stack on push, 2 for empty stack on pop/top, unmodified by isEmpty

Stack *stack_initialize(size_t);
Object pop(Stack *);
void push(Stack *, Object);
Object top(Stack *);
int stack_isEmpty(Stack *);

#endif
