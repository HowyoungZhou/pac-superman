#include <stdlib.h>
#include "linked_list.h"

void ListAddElement(LinkedList *list, void *element) {
    if (list == NULL) return;
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

void OrderedListAddElement(LinkedList *list, void *element, ElementComparer comparer) {
    if (list == NULL) return;
    LinkedListNode *current = list->head, *prev = NULL;
    while (current != NULL) {
        if (comparer(element, current->element) < 0)break;
        prev = current;
        current = current->next;
    }
    LinkedListNode *node = malloc(sizeof(LinkedListNode));
    node->element = element;
    if (!prev) {
        node->next = current;
        list->head = node;
    } else {
        node->next = prev->next;
        prev->next = node;
    }
    if (!node->next) list->tail = node;
    list->length++;
}

void ListPushElement(LinkedList *list, void *element) {
    if (list == NULL) return;
    LinkedListNode *node = malloc(sizeof(LinkedListNode));
    node->element = element;
    node->next = list->head;
    list->head = node;
    if (!list->tail)list->tail = node;
    list->length++;
}

void *ListRemoveElement(LinkedList *list, void *param, ElementIdentifier identifier) {
    if (list == NULL) return NULL;
    LinkedListNode *current = list->head, *last = NULL;
    while (current) {
        if (identifier(current->element, param)) {
            // 如果 last 为 NULL，则修改首节点为下一个节点
            if (last == NULL) list->head = current->next;
            else last->next = current->next;
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

void *ListPopElement(LinkedList *list) {
    if (list == NULL) return NULL;
    LinkedListNode *current = list->head, *last = NULL;
    while (current) {
        // 判断是否到达尾节点
        if (current->next == NULL) {
            if (last == NULL) list->head = NULL;
            else last->next = NULL;
            list->tail = last;
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
    if (list == NULL) return;
    LinkedListNode *node = list->head;
    while (node) {
        LinkedListNode *next = node->next;
        if (destruct) destruct(node->element);
        free(node);
        node = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
}

void ListForEachElement(LinkedList *list, ForEachElementCallback callback) {
    if (list == NULL) return;
    for (LinkedListNode *node = list->head; node != NULL; node = node->next) {
        callback(node->element);
    }
}

void *ListGetLastElement(const LinkedList *list) {
    if (list == NULL || list->tail == NULL)return NULL;
    return list->tail->element;
}

void *ListSearchElement(const LinkedList *list, void *param, ElementIdentifier identifier) {
    if (list->head == NULL)return NULL;
    for (LinkedListNode *node = list->head; node != NULL; node = node->next) {
        if (identifier(node->element, param))return node->element;
    }
    return NULL;
}

bool PointerIdentifier(void *e1, void *e2) {
    return e1 == e2;
}

