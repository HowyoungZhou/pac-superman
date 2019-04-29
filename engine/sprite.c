#include <stdlib.h>
#include <stdio.h>
#include "sprite.h"

static void _DestructSprite(Sprite *this);

static void _DestructSprite(Sprite *this) {
    if (this->hasAnimation && this->renderer.animator != NULL)
        DestructAnimator(this->renderer.animator);
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
    obj->visible = true;
    obj->renderer.Render = NULL;
    obj->Update = NULL;
    obj->Destruct = _DestructSprite;

    return obj;
}
