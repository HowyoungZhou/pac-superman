#include <math.h>
#include <stdlib.h>
#include <tgmath.h>
#include "sprite.h"

void DestructSprite(Sprite *this) {
    if (this->hasAnimation && this->renderer.animator != NULL)
        DestructAnimator(this->renderer.animator);
    free(this);
}

Sprite *ConstructSprite(Vector2 position, Vector2 size, Vector2 velocity) {
    Sprite *obj = malloc(sizeof(Sprite));

    obj->position = position;
    obj->size = size;
    obj->velocity = velocity;
    obj->hasAnimation = false;
    obj->visible = true;
    obj->property = NULL;
    obj->renderer.Render = NULL;
    obj->colliders = (CollidersList) {NULL, NULL};
    obj->Collide = NULL;
    obj->Update = NULL;
    obj->Destruct = DestructSprite;

    return obj;
}

void RegisterCollider(Sprite *sprite, Collider collider) {
    ColliderNode *node = malloc(sizeof(ColliderNode));
    node->collider = collider;
    node->next = NULL;
    if (sprite->colliders.head == NULL) {
        sprite->colliders.head = node;
        sprite->colliders.tail = node;
    } else {
        sprite->colliders.tail->next = node;
        sprite->colliders.tail = node;
    }
}

bool UnregisterCollider(Sprite *sprite, int id) {
    ColliderNode *current = sprite->colliders.head, *last = NULL;
    while (current) {
        if (current->collider.id == id) {
            if (last == NULL) {
                sprite->colliders.head = current->next;
            } else last->next = current->next;
            free(current);
            return true;
        } else {
            last = current;
            current = current->next;
        }
    }
    return false;
}

void RegisterBoxCollider(Sprite *sprite, int id, bool solid, Vector2 size, Vector2 position) {
    Collider collider = {id, solid, BOX_COLLIDER};
    collider.shape.boxCollider = (BoxCollider) {size, position};
    RegisterCollider(sprite, collider);
}

void RegisterCircleCollider(Sprite *sprite, int id, bool solid, Vector2 centre, double radius) {
    Collider collider = {id, solid, CIRCLE_COLLIDER};
    collider.shape.circleCollider = (CircleCollider) {centre, radius};
    RegisterCollider(sprite, collider);
}

Vector2 CalcCentre(Sprite *sprite) {
    return VAdd(sprite->position, VMultiply(0.5, sprite->size));
}

Vector2 CalcRelativeCentre(Sprite *sprite) {
    return VMultiply(0.5, sprite->size);
}

double CalcIncircleRadius(Sprite *sprite) {
    return fmin(sprite->size.x, sprite->size.y) / 2.;
}
