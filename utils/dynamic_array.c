#include <stdlib.h>
#include "dynamic_array.h"

void InitDynamicArray(DynamicArray *array, size_t pageSize) {
    array->elements = calloc(pageSize, sizeof(void *));
    array->pageSize = pageSize;
    array->capacity = pageSize;
    array->length = 0;
}

void ArrayAddElement(DynamicArray *array, void *element) {
    if (!array->elements) return;
    if (array->length >= array->capacity) {
        array->elements = realloc(array->elements, (array->capacity + array->pageSize) * sizeof(void *));
        array->capacity += array->pageSize;
    }
    array->elements[array->length++] = element;
}

void FreeDynamicArray(DynamicArray *array, ElementDestructor destructor) {
    for (long i = 0L; i < array->length; i++) destructor(array->elements[i]);
    free(array->elements);
    array->capacity = 0;
    array->length = 0;
}
