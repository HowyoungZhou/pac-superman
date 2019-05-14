#include <sprite.h>
#include <assets.h>
#include <extgraph.h>
#include <controller.h>
#include <exception.h>
#include "example_bitmap_sprite.h"

#define SPEED 1
static BitmapAsset *_asset;
static int _objCount = 0;

static void _Render(Sprite *this) {
    DrawBitmapAsset(_asset, this->position, this->size);
}

static void _Destruct(Sprite *this) {
    _objCount--;
    if (_objCount == 0) {
        FreeBitmapAsset(_asset);
        _asset = NULL;
    }
    DestructSprite(this);
}

Sprite *ConstructExampleBitmapSprite() {
    Sprite *obj = ConstructSprite(ZERO_VECTOR, (Vector2) {0.3, 0.3}, ZERO_VECTOR);
    if (_asset == NULL)_asset = LoadBitmapAsset("blinky-down1.bmp");
    obj->renderer.Render = _Render;
    _objCount++;
    return obj;
}
