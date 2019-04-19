#include <stdlib.h>
#include <stdio.h>
#include "sprite.h"

void _RenderSprite(Sprite *this) {
    fputs("A sprite without animation must implement Render method of its renderer.", stderr);
    exit(EXIT_FAILURE);
}

void _DestructSprite(Sprite *this) {
    free(this);
}

Sprite *ConstructSprite(Vector2 position, Vector2 size, Vector2 velocity) {
    Sprite *obj = malloc(sizeof(Sprite));

    obj->position = position;
    obj->size = size;
    obj->velocity = velocity;
    obj->collidable = false;
    obj->hasAnimation = false;
    obj->solid = false;

    obj->renderer.Render = _RenderSprite;
    obj->Destruct = _DestructSprite;

    return obj;
}
