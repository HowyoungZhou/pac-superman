#include <sprite.h>
#include <assets.h>
#include <extgraph.h>
#include <controller.h>
#include <exception.h>
#include <engine.h>
#include "example_bitmap_sprite.h"

#define SPEED 1
static BitmapAsset *_asset;
static int _objCount = 0;
static double _interval = 0;

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

static void _Update(Sprite *this, double interval) {
    _interval += interval;
    if (_interval < 500) return;
    SetNavTargetSprite(GetCurrentScene(), this, this->property);
    _interval = 0;
}

Sprite *ConstructExampleBitmapSprite(Sprite *target) {
    Sprite *obj = ConstructSprite((Vector2) {6.45, 6}, (Vector2) {0.3, 0.3}, ZERO_VECTOR);
    RegisterBoxCollider(obj, 0, true, obj->size, ZERO_VECTOR);
    if (_asset == NULL)_asset = LoadBitmapAsset("blinky-down1.bmp");
    obj->property = target;
    obj->renderer.Render = _Render;
    obj->Update = _Update;
    _objCount++;
    return obj;
}
