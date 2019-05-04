#ifndef PAC_SUPERMAN_LINKED_LIST_H
#define PAC_SUPERMAN_LINKED_LIST_H

#include <stdbool.h>

typedef bool (*ElementComparer)(void *e1, void *e2);

typedef void (*ForEachElementCallback)(void *sprite);

typedef struct linkedListNode {
    void *element;
    struct linkedListNode *next;
} LinkedListNode;

typedef struct linkedList {
    struct linkedListNode *head;
    struct linkedListNode *tail;
    unsigned int length;
} LinkedList;

void AddElement(LinkedList *list, void *element);

void *RemoveElement(LinkedList *list, void *element, ElementComparer comparer);

void ForEachElement(LinkedList *list, ForEachElementCallback callback);

#endif //PAC_SUPERMAN_LINKED_LIST_H
