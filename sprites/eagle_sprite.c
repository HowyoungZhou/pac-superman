#include <sprite.h>
#include <vector2.h>
#include <extgraph.h>
#include <drawing.h>
#include <animator.h>
#include <assets.h>
#include <controller.h>
#include <game_scene.h>
#include "eagle_sprite.h"

#define SPEED 1

static BitmapAsset *_eagleAssets[2];

static void _Render(Sprite *this);

static void _Update(Sprite *this, double interval);

static void _Render(Sprite *this) {

    StartFilledRegion(1.);
    if (this->velocity.x >= 0 || this->velocity.y > 0) {
        DrawBitmapAsset(_eagleAssets[0], this->position, this->size);
    } else if (this->velocity.x < 0 || this->velocity.y <= 0) {
        DrawBitmapAsset(_eagleAssets[1], this->position, this->size);
    }
    EndFilledRegion();
}

static void _Update(Sprite *this, double interval) {
    // 通过 Controller 更新速度
    this->velocity = VMultiply(SPEED, GetNormalizedControllerVector());
}

static void _Destruct(Sprite *this) {
    for (int i = 0; i < sizeof(_eagleAssets) / sizeof(BitmapAsset *); i++) FreeBitmapAsset(_eagleAssets[i]);
    DestructSprite(this);
}

Sprite *ConstructEagleSprite(Vector2 position, Vector2 size) {
    Sprite *obj = ConstructSprite(position, size, ZERO_VECTOR);

    obj->name = "PacMan";
    obj->renderer.Render = _Render;
    obj->Update = _Update;
    obj->Destruct = _Destruct;
    RegisterBoxCollider(obj, DEFAULT_COLLIDER_ID, true, size, ZERO_VECTOR);

    _eagleAssets[0] = LoadBitmapAsset("eagle/eagle-right.bmp");
    _eagleAssets[1] = LoadBitmapAsset("eagle/eagle-left.bmp");
    GetCurrentHeros()->pacman = obj;
    return obj;
}

