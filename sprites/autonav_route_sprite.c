#include <sprite.h>
#include <autonav.h>
#include <graphics.h>
#include <engine.h>
#include "autonav_route_sprite.h"

struct Property {
    Sprite *source;
    Sprite *target;
};

static void _Render(Sprite *this);

static void _Render(Sprite *this) {
    Sprite *source = this->property;
    for (PathNode *node = source->navAgent.path; node != NULL && node->parent != NULL; node = node->parent) {
        MovePen(node->position.x, node->position.y);
        Vector2 delta = VSubtract(node->parent->position, node->position);
        DrawLine(delta.x, delta.y);
    }
}

Sprite *ConstructAutoNavRouteSprite(Sprite *source) {
    Sprite *obj = ConstructSprite(ZERO_VECTOR, ZERO_VECTOR, ZERO_VECTOR);
    obj->property = source;
    obj->renderer.Render = _Render;
    obj->foreColor = "Red";
    return obj;
}