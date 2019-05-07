#ifndef PAC_SUPERMAN_LINKED_LIST_H
#define PAC_SUPERMAN_LINKED_LIST_H

#include <stdbool.h>
#define EMPTY_LINKED_LIST (LinkedList){NULL, NULL, 0}
typedef int (*ElementComparer)(void *e1, void *e2);

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

int PointerComparer(void *e1, void *e2);

#endif //PAC_SUPERMAN_LINKED_LIST_H
