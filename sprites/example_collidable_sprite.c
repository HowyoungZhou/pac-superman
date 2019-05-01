#include <vector2.h>
#include <sprite.h>
#include <extgraph.h>
#include <drawing.h>
#include <controller.h>
#include "example_collidable_sprite.h"

static void _Render(Sprite *this);

static void _Update(Sprite *this, double interval);

static void _Collide(Sprite *this, int id, Sprite *other);

static void _Render(Sprite *this) {
    DrawVectorRectangle(this->position, this->size);
}

static void _Collide(Sprite *this, int id, Sprite *other) {
    // 发生碰撞时使对方静止
    other->velocity = ZERO_VECTOR;
}

Sprite *ConstructExampleCollidableSprite(Vector2 position, Vector2 size, Vector2 velocity) {
    // 创建一个 Sprite
    Sprite *obj = ConstructSprite(position, size, velocity);
    obj->renderer.Render = _Render;
    obj->Collide = _Collide;
    RegisterBoxCollider(obj, 0, true, size, ZERO_VECTOR);
    return obj;
}
