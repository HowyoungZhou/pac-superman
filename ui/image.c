#include <sprite.h>
#include <assets.h>
#include <extgraph.h>
#include <controller.h>
#include <exception.h>
#include "image.h"

static void _Render(Sprite *this) {
    DrawBitmapAsset(this->property, this->position, this->size);
}

static void _Destruct(Sprite *this) {
    FreeBitmapAsset(this->property);
    DestructSprite(this);
}

Sprite *ConstructImageSprite(Vector2 position, Vector2 size, string imageFile) {
    Sprite *obj = ConstructSprite(position, size, ZERO_VECTOR);
    obj->property = LoadBitmapAsset(imageFile);
    obj->renderer.Render = _Render;
    return obj;
}
