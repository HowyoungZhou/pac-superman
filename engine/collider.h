#ifndef PAC_SUPERMAN_COLLIDER_H
#define PAC_SUPERMAN_COLLIDER_H

#include <vector2.h>

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

void DetectCollision(Sprite *s1, Sprite *s2, double interval);

#endif //PAC_SUPERMAN_COLLIDER_H
