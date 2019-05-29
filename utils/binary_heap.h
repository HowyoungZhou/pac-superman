#ifndef PAC_SUPERMAN_BINARY_HEAP_H
#define PAC_SUPERMAN_BINARY_HEAP_H

#define PAGE_SIZE 1000

typedef int (*ElementComparer)(void *e1, void *e2);

typedef bool (*ElementIdentifier)(void *element, void *param);

typedef struct BinaryHeap {
    void **elements;
    unsigned int length;
    unsigned int capacity;
    ElementComparer comparer;
} BinaryHeap;

void InitBinaryHeap(BinaryHeap *heap, ElementComparer comparer);

void InsertElement(BinaryHeap *heap, void *element);

void *PopTop(BinaryHeap *heap);

void *SearchElement(BinaryHeap *heap, void *param, ElementIdentifier identifier);

void *PopElement(BinaryHeap *heap, void *param, ElementIdentifier identifier);

#endif //PAC_SUPERMAN_BINARY_HEAP_H
