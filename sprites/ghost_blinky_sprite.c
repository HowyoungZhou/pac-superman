#include <sprite.h>
#include <assets.h>
#include <extgraph.h>
#include <controller.h>
#include <exception.h>
#include <engine.h>
#include <game_controller.h>
#include <autonav.h>
#include "ghost_blinky_sprite.h"

#define SPEED 1

static BitmapAsset *_asset;
static int _objCount = 0;
static double _interval = 0;

static void _AnimatedGhostBlinkySprite(Animator *this, Sprite *sprite, Frame frame);

static void _AnimatedGhostBlinkySprite(Animator *this, Sprite *sprite, Frame frame) {
    //StartFilledRegion(0);
    if(sprite->velocity.x>0){
        if(frame == 0) _asset = LoadBitmapAsset("ghost/blinky/blinky-right1.bmp");
        else _asset = LoadBitmapAsset("ghost/blinky/blinky-right2.bmp");
    }
    else if(sprite->velocity.y>0){
        if(frame == 0) _asset = LoadBitmapAsset("ghost/blinky/blinky-up1.bmp");
        else _asset = LoadBitmapAsset("ghost/blinky/blinky-up2.bmp");
    }
    else if(sprite->velocity.x<0){
        if(frame == 0) _asset = LoadBitmapAsset("ghost/blinky/blinky-left1.bmp");
        else _asset = LoadBitmapAsset("ghost/blinky/blinky-left2.bmp");
    }
    else {
        if(frame == 0) _asset = LoadBitmapAsset("ghost/blinky/blinky-down1.bmp");
        else _asset = LoadBitmapAsset("ghost/blinky/blinky-down2.bmp");
    }
    DrawBitmapAsset(_asset, sprite->position, sprite->size);
    //EndFilledRegion();
}

/*static void _Render(Sprite *this);

void _Render(Sprite *this) {
    DrawBitmapAsset(_asset, this->position, this->size);
}
 //*/

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
    UpdatePath(GetCurrentScene(), this);
    _interval = 0;
}

/*static void _Collide(Sprite *this, int id, Sprite *other) {
    if (other->name && !strcmp(other->name, "PacMan")) {
        if (GetPowerMode()) this->visible = false;
        else PopScene();
    }
}*/

Sprite *ConstructGhostBlinkySprite(Sprite *target) {
    Sprite *obj = ConstructSprite((Vector2) {6.45, 6}, (Vector2) {0.3, 0.3}, ZERO_VECTOR);
    RegisterBoxCollider(obj, 0, true, obj->size, ZERO_VECTOR);
    //if (_asset == NULL)_asset = LoadBitmapAsset("blinky-down1.bmp");
    SetNavTargetSprite(obj, target);

    Animator *animator = ConstructAnimator(2);
    animator->Animate = _AnimatedGhostBlinkySprite;
    for (int i = 0; i < 2; i++)animator->intervals[i] = 200;

    obj->name = "GhostBlinky";
    obj->hasAnimation = true;
    obj->renderer.animator = animator;
    obj->Update = _Update;
    //obj->Collide = _Collide;
    _objCount++;
    return obj;
}
