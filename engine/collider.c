#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "collider.h"
#include "sprite.h"
#include <vector2.h>

static bool _CircleIntersect(const CircleCollider *c1, const CircleCollider *c2);

static bool _BoxIntersect(const BoxCollider *c1, const BoxCollider *c2);

static bool _BoxCircleIntersect(const BoxCollider *c1, const CircleCollider *c2);

static bool _CircleIntersect(const CircleCollider *c1, const CircleCollider *c2) {
    return VDistance(c1->centre, c2->centre) < (c1->radius + c2->radius);
}

static bool _BoxIntersect(const BoxCollider *c1, const BoxCollider *c2) {
    Vector2 c1r = VAdd(c1->position, c1->size);
    Vector2 c2r = VAdd(c2->position, c2->size);
    return c1->position.x < c2r.x && c1r.x > c2->position.x && c1r.y > c2->position.y && c1->position.y < c2r.y;
}

static bool _BoxCircleIntersect(const BoxCollider *c1, const CircleCollider *c2) {
    Vector2 boxCentre = VAdd(c1->position, VMultiply(0.5, c1->size));
    Vector2 firstQuadrant = VAbs(VSubtract(c2->centre, boxCentre));
    Vector2 shortest = VMax(VSubtract(firstQuadrant, VMultiply(0.5, c1->size)), ZERO_VECTOR);
    return VLengthSquared(shortest) < c2->radius * c2->radius;
}

bool DetectIntersection(const Collider *c1, const Collider *c2) {
    switch (c1->type) {
        case BOX_COLLIDER:
            return c2->type == BOX_COLLIDER ? _BoxIntersect(&c1->shape.boxCollider, &c2->shape.boxCollider)
                                           : _BoxCircleIntersect(&c1->shape.boxCollider, &c2->shape.circleCollider);
        case CIRCLE_COLLIDER:
            return c2->type == BOX_COLLIDER ? _BoxCircleIntersect(&c2->shape.boxCollider, &c1->shape.circleCollider)
                                           : _CircleIntersect(&c1->shape.circleCollider, &c2->shape.circleCollider);
    }
}

Collider *ConstructCollider(int id, ColliderType type, bool solid) {
    Collider *obj = malloc(sizeof(Collider));
    obj->id = id;
    obj->type = type;
    obj->solid = solid;
    return obj;
}

void DestructCollider(Collider *this) {
    free(this);
}
