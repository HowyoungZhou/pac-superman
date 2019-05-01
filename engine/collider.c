#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "collider.h"
#include "sprite.h"
#include <vector2.h>

static bool _CircleIntersect(CircleCollider c1, CircleCollider c2);

static bool _BoxIntersect(BoxCollider c1, BoxCollider c2);

static bool _BoxCircleIntersect(BoxCollider c1, CircleCollider c2);

static Collider _CalcAbsolutePosition(Sprite *sprite, Collider collider, double interval);

static bool _DetectIntersection(Collider c1, Collider c2);

static bool _CircleIntersect(CircleCollider c1, CircleCollider c2) {
    return VDistance(c1.centre, c2.centre) < (c1.radius + c2.radius);
}

static bool _BoxIntersect(BoxCollider c1, BoxCollider c2) {
    Vector2 c1r = VAdd(c1.position, c1.size);
    Vector2 c2r = VAdd(c2.position, c2.size);
    return c1.position.x < c2r.x && c1r.x > c2.position.x && c1r.y > c2.position.y && c1.position.y < c2r.y;
}

static bool _BoxCircleIntersect(BoxCollider c1, CircleCollider c2) {
    Vector2 boxCentre = VAdd(c1.position, VMultiply(0.5, c1.size));
    Vector2 fisrtQuadrant = VAbs(VSubtract(c2.centre, boxCentre));
    Vector2 shortest = VMax(VSubtract(fisrtQuadrant, VMultiply(0.5, c1.size)), ZERO_VECTOR);
    return VLengthSquared(shortest) < c2.radius * c2.radius;
}

static Collider _CalcAbsolutePosition(Sprite *sprite, Collider collider, double interval) {
    Vector2 position = VAdd(sprite->position, VMultiply(interval / 1000.0, sprite->velocity));
    switch (collider.type) {
        case BOX_COLLIDER:
            collider.shape.boxCollider.position = VAdd(position, collider.shape.boxCollider.position);
            break;
        case CIRCLE_COLLIDER:
            collider.shape.circleCollider.centre = VAdd(position, collider.shape.circleCollider.centre);
            break;
    }
    return collider;
}

static bool _DetectIntersection(Collider c1, Collider c2) {
    switch (c1.type) {
        case BOX_COLLIDER:
            return c2.type == BOX_COLLIDER ? _BoxIntersect(c1.shape.boxCollider, c2.shape.boxCollider)
                                           : _BoxCircleIntersect(c1.shape.boxCollider, c2.shape.circleCollider);
        case CIRCLE_COLLIDER:
            return c2.type == BOX_COLLIDER ? _BoxCircleIntersect(c2.shape.boxCollider, c1.shape.circleCollider)
                                           : _CircleIntersect(c1.shape.circleCollider, c2.shape.circleCollider);
    }
}

void DetectCollision(Sprite *s1, Sprite *s2, double interval) {
    if (s1->colliders.head == NULL || s2->colliders.head == NULL)return;
    for (ColliderNode *n1 = s1->colliders.head; n1 != NULL; n1 = n1->next) {
        for (ColliderNode *n2 = s2->colliders.head; n2 != NULL; n2 = n2->next) {
            if (!_DetectIntersection(_CalcAbsolutePosition(s1, n1->collider, interval),
                                     _CalcAbsolutePosition(s2, n2->collider, interval)))
                continue;
            if (s1->Collide != NULL) s1->Collide(s1, n1->collider.id, s2);
            if (s2->Collide != NULL)s2->Collide(s2, n2->collider.id, s1);
        }
    }
}
