#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binary_heap.h"

#define PARENT(i) (((i) - 1) >> 1)
#define LEFT_CHILD(i) (((i) << 1) + 1)
#define RIGHT_CHILD(i) (((i) >> 1) + 2)

static inline void _HeapifyUp(BinaryHeap *heap, int index);

static inline void _HeapifyDown(BinaryHeap *heap, int index);

void InitBinaryHeap(BinaryHeap *heap, ElementComparer comparer) {
    heap->elements = calloc(PAGE_SIZE, sizeof(void *));
    heap->comparer = comparer;
    heap->capacity = PAGE_SIZE;
    heap->length = 0;
}

void FreeBinaryHeap(BinaryHeap *heap) {
    free(heap->elements);
}

static inline void _HeapifyUp(BinaryHeap *heap, int index) {
    ElementComparer compare = heap->comparer;
    void *curNode = heap->elements[index];
    int parent = PARENT(index);
    for (; index > 0; index = parent, parent = PARENT(parent)) {
        if (compare(heap->elements[parent], curNode) < 0)break;
        heap->elements[index] = heap->elements[parent];
    }
    heap->elements[index] = curNode;
}

void HeapInsertElement(BinaryHeap *heap, void *element) {
    if (heap->length >= heap->capacity) {
        heap->elements = realloc(heap->elements, (heap->capacity + PAGE_SIZE) * sizeof(void *));
        heap->capacity = heap->capacity + PAGE_SIZE;
    }
    heap->elements[heap->length++] = element;
    _HeapifyUp(heap, heap->length - 1);
}

static inline void _HeapifyDown(BinaryHeap *heap, int index) {
    ElementComparer compare = heap->comparer;
    int cur = LEFT_CHILD(index);
    void *node = heap->elements[index];
    int length = heap->length;
    for (; cur < length; index = cur, cur = LEFT_CHILD(cur)) {
        if (cur + 1 < length && compare(heap->elements[cur + 1], heap->elements[cur]) < 0)cur++;
        if (compare(node, heap->elements[cur]) <= 0)break;
        heap->elements[index] = heap->elements[cur];
    }
    heap->elements[index] = node;
}


void *HeapPopTop(BinaryHeap *heap) {
    if (!heap->length) return NULL;
    void *top = heap->elements[0];
    heap->elements[0] = heap->elements[--heap->length];
    _HeapifyDown(heap, 0);
    return top;
}

int HeapSearchIndexOfElement(BinaryHeap *heap, void *param, ElementIdentifier identifier) {
    for (int i = 0; i < heap->length; i++) {
        if (identifier(heap->elements[i], param)) return i;
    }
    return ELEMENT_NOT_FOUND;
}

void *HeapSearchElement(BinaryHeap *heap, void *param, ElementIdentifier identifier) {
    int res = HeapSearchIndexOfElement(heap, param, identifier);
    if (res == ELEMENT_NOT_FOUND) return NULL;
    return heap->elements[res];
}

void *HeapPopElement(BinaryHeap *heap, void *param, ElementIdentifier identifier) {
    int res = HeapSearchIndexOfElement(heap, param, identifier);
    if (res == ELEMENT_NOT_FOUND) return NULL;
    void *element = heap->elements[res];
    heap->elements[res] = heap->elements[--heap->length];
    _HeapifyDown(heap, res);
    return element;
}

bool HeapUpdateElementByIndex(BinaryHeap *heap, int index) {
    if (index == ELEMENT_NOT_FOUND) return false;
    _HeapifyDown(heap, index);
    _HeapifyUp(heap, index);
    return true;
}

bool HeapUpdateElement(BinaryHeap *heap, void *param, ElementIdentifier identifier) {
    int index = HeapSearchIndexOfElement(heap, param, identifier);
    return HeapUpdateElementByIndex(heap, index);
}
