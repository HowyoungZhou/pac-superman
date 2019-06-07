#ifndef PAC_SUPERMAN_DYNAMIC_ARRAY_H
#define PAC_SUPERMAN_DYNAMIC_ARRAY_H

#define EMPTY_DYNAMIC_ARRAY (DynamicArray) {NULL, 0, 0, 0}
#define ArrayGetElement(array, type, i) ((type)array.elements[i])

typedef void (*ElementDestructor)(void *obj);

typedef struct DynamicArray {
    void **elements;
    size_t length;
    size_t capacity;
    size_t pageSize;
} DynamicArray;

void InitDynamicArray(DynamicArray *array, size_t pageSize);

void ArrayAddElement(DynamicArray *array, void *element);

void FreeDynamicArray(DynamicArray *array, ElementDestructor destructor);

#endif //PAC_SUPERMAN_DYNAMIC_ARRAY_H
