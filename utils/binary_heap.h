#ifndef PAC_SUPERMAN_BINARY_HEAP_H
#define PAC_SUPERMAN_BINARY_HEAP_H

#define PAGE_SIZE 1000

#define ELEMENT_NOT_FOUND -1

typedef int (*ElementComparer)(void *e1, void *e2);

typedef bool (*ElementIdentifier)(void *element, void *param);

typedef struct BinaryHeap {
    void **elements;
    unsigned int length;
    unsigned int capacity;
    ElementComparer comparer;
} BinaryHeap;

void InitBinaryHeap(BinaryHeap *heap, ElementComparer comparer);

void FreeBinaryHeap(BinaryHeap *heap);

void HeapInsertElement(BinaryHeap *heap, void *element);

void *HeapPopTop(BinaryHeap *heap);

int HeapSearchIndexOfElement(BinaryHeap *heap, void *param, ElementIdentifier identifier);

void *HeapSearchElement(BinaryHeap *heap, void *param, ElementIdentifier identifier);

void *HeapPopElement(BinaryHeap *heap, void *param, ElementIdentifier identifier);

bool HeapUpdateElementByIndex(BinaryHeap *heap, int index);

bool HeapUpdateElement(BinaryHeap *heap, void *param, ElementIdentifier identifier);

#endif //PAC_SUPERMAN_BINARY_HEAP_H
