#include <sprite.h>
#include <vector2.h>
#include <extgraph.h>
#include <drawing.h>
#include <animator.h>
#include <assets.h>
#include <controller.h>
#include "eagle_sprite.h"

#define SPEED 1

static BitmapAsset *_eagleAssets[2];

static void _AnimatedEagleSprite(Animator *this, Sprite *sprite, Frame frame);

static void _Update(Sprite *this, double interval);

static void _AnimatedEagleSprite(Animator *this, Sprite *sprite, Frame frame) {

    StartFilledRegion(1.);
    if (sprite->velocity.x >= 0 || sprite->velocity.y > 0) {
        DrawBitmapAsset(_eagleAssets[0], sprite->position, sprite->size);
    } else if (sprite->velocity.x < 0 || sprite->velocity.y <= 0) {
        DrawBitmapAsset(_eagleAssets[1], sprite->position, sprite->size);
    }
    EndFilledRegion();
}

static void _Update(Sprite *this, double interval) {
    // 通过 Controller 更新速度
    this->velocity = VMultiply(SPEED, GetNormalizedControllerVector());
}

Sprite *ConstructEagleSprite(Vector2 position, Vector2 size) {
    Sprite *obj = ConstructSprite(position, size, ZERO_VECTOR);

    Animator *animator = ConstructAnimator(5);
    for (int i = 0; i < 5; i++) animator->intervals[i] = 80;
    animator->reverse = true;
    animator->Animate = _AnimatedEagleSprite;

    obj->name = "PacMan";
    obj->hasAnimation = true;
    obj->renderer.animator = animator;
    obj->Update = _Update;
    RegisterCircleCollider(obj, DEFAULT_COLLIDER_ID, true, CalcRelativeCentre(obj), CalcIncircleRadius(obj));

    _eagleAssets[0] = LoadBitmapAsset("eagle/eagle-right.bmp");
    _eagleAssets[1] = LoadBitmapAsset("eagle/eagle-left.bmp");
    return obj;
}

