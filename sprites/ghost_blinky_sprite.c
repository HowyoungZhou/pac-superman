#include <sprite.h>
#include <assets.h>
#include <extgraph.h>
#include <controller.h>
#include <exception.h>
#include <engine.h>
#include <game_controller.h>
#include <autonav.h>
#include "ghost_blinky_sprite.h"

typedef enum {
    UP, RIGHT, DOWN, LEFT
} Direction;

typedef struct {
    BitmapAsset *assets[8];
    Direction lookingAt;
} Ghost;

static inline Ghost *_ConstructGhost();

static inline void _DestructGhost(Ghost *this);

static void _Animate(Animator *this, Sprite *sprite, Frame frame);

static BitmapAsset *_assets[8];
static int _objCount = 0;
static double _interval = 0;

static inline Ghost *_ConstructGhost() {
    Ghost *obj = malloc(sizeof(Ghost));
    obj->lookingAt = DOWN;
    obj->assets[0] = LoadBitmapAsset("ghost/blinky/blinky-right1.bmp");
    obj->assets[1] = LoadBitmapAsset("ghost/blinky/blinky-right2.bmp");
    obj->assets[2] = LoadBitmapAsset("ghost/blinky/blinky-up1.bmp");
    obj->assets[3] = LoadBitmapAsset("ghost/blinky/blinky-up2.bmp");
    obj->assets[4] = LoadBitmapAsset("ghost/blinky/blinky-left1.bmp");
    obj->assets[5] = LoadBitmapAsset("ghost/blinky/blinky-left2.bmp");
    obj->assets[6] = LoadBitmapAsset("ghost/blinky/blinky-down1.bmp");
    obj->assets[7] = LoadBitmapAsset("ghost/blinky/blinky-down2.bmp");
    return obj;
}

static inline void _DestructGhost(Ghost *this) {
    for (int i = 0; i < 8; i++) {
        FreeBitmapAsset(this->assets[i]);
    }
    free(this);
}

static void _Animate(Animator *this, Sprite *sprite, Frame frame) {
    Ghost *ghost = sprite->property;
    if (sprite->velocity.x > 0) {
        ghost->lookingAt = RIGHT;
    } else if (sprite->velocity.y > 0) {
        ghost->lookingAt = UP;
    } else if (sprite->velocity.x < 0) {
        ghost->lookingAt = LEFT;
    } else if (sprite->velocity.y < 0) {
        ghost->lookingAt = DOWN;
    }

    switch (ghost->lookingAt) {
        case RIGHT:
            if (frame == 0) DrawBitmapAsset(ghost->assets[0], sprite->position, sprite->size);
            else DrawBitmapAsset(ghost->assets[1], sprite->position, sprite->size);
            break;
        case UP:
            if (frame == 0) DrawBitmapAsset(ghost->assets[2], sprite->position, sprite->size);
            else DrawBitmapAsset(ghost->assets[3], sprite->position, sprite->size);
            break;
        case LEFT:
            if (frame == 0) DrawBitmapAsset(ghost->assets[4], sprite->position, sprite->size);
            else DrawBitmapAsset(ghost->assets[5], sprite->position, sprite->size);
            break;
        case DOWN:
            if (frame == 0) DrawBitmapAsset(ghost->assets[6], sprite->position, sprite->size);
            else DrawBitmapAsset(ghost->assets[7], sprite->position, sprite->size);
            break;
    }
}

static void _Destruct(Sprite *this) {
    _DestructGhost(this->property);
    DestructSprite(this);
}

static void _Update(Sprite *this, double interval) {
    _interval += interval;
    if (_interval < 500) return;
    UpdatePath(GetCurrentScene(), this);
    _interval = 0;
}

static void _Collide(Sprite *this, int id, Sprite *other) {
    if (other->name && !strcmp(other->name, "PacMan")) {
        if (GetPowerMode()) this->visible = false;
        else PopScene();
    }
}

Sprite *ConstructGhostBlinkySprite(Sprite *target) {
    Sprite *obj = ConstructSprite((Vector2) {6.45, 6}, (Vector2) {0.3, 0.3}, ZERO_VECTOR);

    Ghost *ghost = _ConstructGhost();

    RegisterBoxCollider(obj, 0, true, obj->size, ZERO_VECTOR);
    SetNavTargetSprite(obj, target);

    Animator *animator = ConstructAnimator(2);
    animator->Animate = _Animate;
    for (int i = 0; i < 2; i++)animator->intervals[i] = 200;

    obj->name = "GhostBlinky";
    obj->hasAnimation = true;
    obj->renderer.animator = animator;
    obj->Update = _Update;
    obj->property = ghost;
    obj->Collide = _Collide;
    _objCount++;
    return obj;
}
