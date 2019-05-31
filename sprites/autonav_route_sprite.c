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
    struct Property *property = this->property;
    PathNode *path = AStarFindPath(GetCurrentScene(), property->source, property->target);
    PathNode *child = NULL;
    for (; path != NULL && path->parent != NULL; path = path->parent) {
        if (child != NULL)free(child);
        MovePen(path->position.x, path->position.y);
        Vector2 delta = VSubtract(path->parent->position, path->position);
        DrawLine(delta.x, delta.y);
        child = path;
    }
}

Sprite *ConstructAutoNavRouteSprite(Sprite *source, Sprite *target) {
    Sprite *obj = ConstructSprite(ZERO_VECTOR, ZERO_VECTOR, ZERO_VECTOR);
    struct Property *property = malloc(sizeof(struct Property));
    property->source = source;
    property->target = target;
    obj->property = property;
    obj->renderer.Render = _Render;
    obj->foreColor = "Red";
    return obj;
}