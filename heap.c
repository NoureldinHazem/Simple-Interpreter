#include <stdlib.h>
#include "heap.h"

struct Heap {
    Variable **arr;
    size_t count;
    size_t capacity;
};

Heap* initHeap(size_t capacity) {
    Heap *mh = malloc(sizeof(Heap));
    mh->arr = malloc(sizeof(Variable *) * capacity);

    mh->capacity = capacity;
    mh->count = 0;

    return mh;
}

void insertToHeap(Heap *mh, Variable *var) {
    if (mh->count >= mh->capacity)
        return;

    mh->arr[mh->count++] = var;
}

static void minHeapify(Variable **arr, int i) {
    int parent_index = (i-1)/2;

    if (arr[parent_index]->val > arr[i]->val) {
        Variable *tmp = arr[parent_index];
        arr[parent_index] = arr[i];
        arr[i] = tmp;
        minHeapify(arr, parent_index);
    }
}

Variable *popMin(Heap *mh) {
    Variable *min = NULL;

    if (!mh->count)
        return min;

    // build heap
    for (int i = mh->count; i > 1; --i)
        minHeapify(mh->arr, i - 2);

    // swap first with last, then cut tail
    min = mh->arr[0];
    mh->arr[0] = mh->arr[mh->count - 1];
    mh->count--;

    if (mh->count > 1)
        minHeapify(mh->arr, mh->count - 1);
    else if (mh->count == 1)
        minHeapify(mh->arr, 1);

    return min;
}
