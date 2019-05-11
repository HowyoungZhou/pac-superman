/**@file collider.h
 * @brief 该文件包含了 Collider 类的定义及相关方法。
 */
#ifndef PAC_SUPERMAN_COLLIDER_H
#define PAC_SUPERMAN_COLLIDER_H

#include <vector2.h>
#include <linked_list.h>

#define DEFAULT_COLLIDER_ID 0

struct sprite;
typedef struct sprite Sprite;

typedef enum {
    BOX_COLLIDER, CIRCLE_COLLIDER
} ColliderType;

typedef struct {
    Vector2 size;
    Vector2 position;
} BoxCollider;

typedef struct {
    Vector2 centre;
    double radius;
} CircleCollider;

typedef struct {
    int id;
    bool solid;
    ColliderType type;
    union {
        BoxCollider boxCollider;
        CircleCollider circleCollider;
    } shape;
} Collider;

typedef LinkedListNode ColliderNode;

typedef LinkedList CollidersList;

/**@brief Collider 的构造函数。
 *
 * @param id Collider 的 ID
 * @param type Collider 的类型
 * @param solid Collider 是否是坚固的（即是否可以穿过）
 * @return 构造的 Collider
 */
Collider *ConstructCollider(int id, ColliderType type, bool solid);

/**@brief Collider 的析构函数。
 *
 * @param this Collider 对象
 */
void DestructCollider(Collider *this);

/**@brief 执行碰撞检测，该方法由引擎调用。
 *
 * @param s1 Sprite 对象 1
 * @param s2 Sprite 对象 2
 * @param interval 当前渲染时间间隔
 */
void DetectCollision(Sprite *s1, Sprite *s2, double interval);

#endif //PAC_SUPERMAN_COLLIDER_H