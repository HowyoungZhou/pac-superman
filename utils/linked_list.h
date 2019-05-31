#ifndef PAC_SUPERMAN_LINKED_LIST_H
#define PAC_SUPERMAN_LINKED_LIST_H

#include <stdbool.h>

#define EMPTY_LINKED_LIST (LinkedList){NULL, NULL, 0}

typedef bool (*ElementIdentifier)(void *element, void *param);

typedef void (*ElementDestructor)(void *obj);

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

/**@brief 向链表中添加元素。
 *
 * @param list 目标链表
 * @param element 要添加的元素
 */
void AddElement(LinkedList *list, void *element);

/**@brief 弹出链表中的最末尾的元素并将其返回。
 *
 * @param list 目标链表
 * @return 如成功则返回最末尾的元素，否则返回 NULL
 */
void *PopElement(LinkedList *list);

/**@brief 从链表中移除指定元素。
 *
 * @param list 目标链表
 * @param param 用于匹配元素的参数
 * @param identifier 用于匹配元素的比较器，如该函数返回 0 则表示成功匹配到了该元素。
 * @return 如移除成功则返回被移除的元素，否则返回 NULL
 */
void *RemoveElement(LinkedList *list, void *param, ElementIdentifier identifier);

/**@brief 清除链表中的所有元素。
 *
 * @param list 目标链表
 * @param destruct 用于释放各元素空间的析构函数
 */
void ClearList(LinkedList *list, ElementDestructor destruct);

/**@brief 遍历链表中的所有元素。
 *
 * @param list 目标链表
 * @param callback 用于遍历元素的函数，所有元素将被依次作为参数传入
 */
void ForEachElement(LinkedList *list, ForEachElementCallback callback);

/**@brief 获取链表中最后的元素。
 *
 * @param list 目标链表
 * @return 如链表非空则返回最后的元素，否则返回 NULL
 */
void *GetLastElement(const LinkedList *list);

/**@brief 查找链表中的某元素。
 *
 * @param list 目标链表
 * @param param 用于匹配元素的参数
 * @param identifier 用于匹配元素的比较器，如该函数返回 0 则表示成功匹配到了该元素。
 * @return 如查找成功则返回该元素，否则返回 NULL
 */
void *SearchElement(const LinkedList *list, void *param, ElementIdentifier identifier);

/**@brief 用于比较两元素是否位于同一地址的指针比较器。
 *
 * @param e1 元素 1
 * @param e2 元素 2
 * @return 如两元素位于同一地址则返回 true，否则返回 false。
 */
bool PointerComparer(void *e1, void *e2);

#endif //PAC_SUPERMAN_LINKED_LIST_H
