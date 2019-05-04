#include <stdlib.h>
#include "linked_list.h"

void AddElement(LinkedList *list, void *element) {
    LinkedListNode *node = malloc(sizeof(LinkedListNode));
    node->element = element;
    node->next = NULL;
    if (list->head == NULL) {
        list->head = list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    list->length++;
}

void *RemoveElement(LinkedList *list, void *element, ElementComparer comparer) {
    LinkedListNode *current = list->head, *last = NULL;
    while (current) {
        if (comparer(current->element, element)) {
            if (last == NULL) {
                list->head = current->next;
            } else last->next = current->next;
            void *e = current->element;
            free(current);
            list->length--;
            return e;
        } else {
            last = current;
            current = current->next;
        }
    }
    return NULL;
}

void ForEachElement(LinkedList *list, ForEachElementCallback callback) {
    for (LinkedListNode *node = list->head; node != NULL; node = node->next) {
        callback(node->element);
    }
}

