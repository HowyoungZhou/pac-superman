#include <math.h>
#include <stdlib.h>
#include <tgmath.h>
#include "sprite.h"

static bool _ColliderIDComparer(void *collider, void *id);

void DestructSprite(Sprite *this) {
    // 如果 Sprite 有动画，则析构动画器
    if (this->hasAnimation && this->renderer.animator != NULL)
        DestructAnimator(this->renderer.animator);
    // 析构碰撞器
    ClearList(&this->colliders, free);
    // 析构自身
    free(this);
}

Sprite *ConstructSprite(Vector2 position, Vector2 size, Vector2 velocity) {
    Sprite *obj = malloc(sizeof(Sprite));

    obj->position = position;
    obj->size = size;
    obj->velocity = velocity;
    obj->hasAnimation = false;
    obj->visible = true;
    obj->foreColor = "White";
    obj->property = NULL;
    obj->renderer.Render = NULL;
    obj->colliders = EMPTY_LINKED_LIST;
    obj->Collide = NULL;
    obj->Update = NULL;
    obj->Destruct = DestructSprite;

    return obj;
}

void RegisterCollider(Sprite *sprite, Collider *collider) {
    AddElement(&sprite->colliders, collider);
}

static bool _ColliderIDComparer(void *collider, void *id) {
    return ((Collider *) collider)->id == *(int *) id;
}

bool UnregisterCollider(Sprite *sprite, int id) {
    Collider *collider = RemoveElement(&sprite->colliders, &id, _ColliderIDComparer);
    if (collider == NULL)return false;
    DestructCollider(collider);
    return true;
}

void RegisterBoxCollider(Sprite *sprite, int id, bool solid, Vector2 size, Vector2 position) {
    Collider *collider = ConstructCollider(id, BOX_COLLIDER, solid);
    collider->shape.boxCollider = (BoxCollider) {size, position};
    RegisterCollider(sprite, collider);
}

void RegisterCircleCollider(Sprite *sprite, int id, bool solid, Vector2 centre, double radius) {
    Collider *collider = ConstructCollider(id, CIRCLE_COLLIDER, solid);
    collider->shape.circleCollider = (CircleCollider) {centre, radius};
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
