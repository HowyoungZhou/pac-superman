/**@file collider.h
 * @brief 该文件包含了 Collider 类的定义及相关方法。
 */
#ifndef PAC_SUPERMAN_COLLIDER_H
#define PAC_SUPERMAN_COLLIDER_H

#include <vector2.h>

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

typedef struct colliderNode {
    Collider collider;
    struct colliderNode *next;
} ColliderNode;

typedef struct {
    ColliderNode *head;
    ColliderNode *tail;
} CollidersList;

/**@brief 执行碰撞检测，该方法由引擎调用。
 *
 * @param s1 Sprite 对象 1
 * @param s2 Sprite 对象 2
 * @param interval 当前渲染时间间隔
 */
void DetectCollision(Sprite *s1, Sprite *s2, double interval);

#endif //PAC_SUPERMAN_COLLIDER_H
