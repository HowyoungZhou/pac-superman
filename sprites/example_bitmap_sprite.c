#include <sprite.h>
#include <assets.h>
#include <extgraph.h>
#include <controller.h>
#include "example_bitmap_sprite.h"

#define SPEED 1
static BitmapAsset *_asset;

static void _Render(Sprite *this) {
    DrawBitmapAsset(_asset, this->position, this->size);
}

static void _Destruct(Sprite *this) {
    FreeBitmapAsset(_asset);
    DestructSprite(this);
}

Sprite *ConstructExampleBitmapSprite() {
    Sprite *obj = ConstructSprite(ZERO_VECTOR, (Vector2) {0.3, 0.3}, ZERO_VECTOR);
    _asset = LoadBitmapAsset("../assets/blinky-down1.bmp");
    obj->renderer.Render = _Render;
    return obj;
}
