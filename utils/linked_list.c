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
        if (comparer(current->element, element) == 0) {
            // 如果 last 为 NULL，则修改首节点为下一个节点
            if (last == NULL) {
                list->head = current->next;
            } else last->next = current->next;
            // 如果要删除的是尾节点，则更新 tail
            if (current == list->tail)list->tail = last;
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

void ClearList(LinkedList *list, ElementDestructor destruct) {
    LinkedListNode *node = list->head;
    while (node) {
        LinkedListNode *next = node->next;
        destruct(node->element);
        free(node);
        node = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
}

void ForEachElement(LinkedList *list, ForEachElementCallback callback) {
    for (LinkedListNode *node = list->head; node != NULL; node = node->next) {
        callback(node->element);
    }
}

int PointerComparer(void *e1, void *e2) {
    return e1 - e2;
}

