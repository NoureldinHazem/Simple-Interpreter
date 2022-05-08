#ifndef HEAP_H
#define HEAP_H

#include "varstruct.h"

struct Heap;
typedef struct Heap Heap;

Heap* initHeap(size_t capacity);
void insertToHeap(Heap *mh, Variable *var);
Variable *popMin(Heap *mh);

#endif
