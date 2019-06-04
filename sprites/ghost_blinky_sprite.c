#include <sprite.h>
#include <assets.h>
#include <extgraph.h>
#include <controller.h>
#include <exception.h>
#include <engine.h>
#include <game_controller.h>
#include <autonav.h>
#include "ghost_blinky_sprite.h"
#include "ghost.h"
#include "map_sprite.h"
#include <ghost.h>

static inline Ghost *_ConstructGhost();

static inline void _DestructGhost(Ghost *this);

static void _Animate(Animator *this, Sprite *sprite, Frame frame);

static void _UpdatePath(Sprite *this);

static Vector2 _FindFleePosition(Sprite *map);

static int _objCount = 0;
static double _interval = 0;

static inline Ghost *_ConstructGhost() {
    Ghost *obj = malloc(sizeof(Ghost));
    obj->lookingAt = DOWN;
    obj->chasedAfter = false;
    obj->assets[0] = LoadBitmapAsset("ghost/blinky/blinky-right1.bmp");
    obj->assets[1] = LoadBitmapAsset("ghost/blinky/blinky-right2.bmp");
    obj->assets[2] = LoadBitmapAsset("ghost/blinky/blinky-up1.bmp");
    obj->assets[3] = LoadBitmapAsset("ghost/blinky/blinky-up2.bmp");
    obj->assets[4] = LoadBitmapAsset("ghost/blinky/blinky-left1.bmp");
    obj->assets[5] = LoadBitmapAsset("ghost/blinky/blinky-left2.bmp");
    obj->assets[6] = LoadBitmapAsset("ghost/blinky/blinky-down1.bmp");
    obj->assets[7] = LoadBitmapAsset("ghost/blinky/blinky-down2.bmp");
    obj->assets[8] = LoadBitmapAsset("ghost/flash/flash1.bmp");
    obj->assets[9] = LoadBitmapAsset("ghost/flash/flash2.bmp");
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

    if (ghost->chasedAfter) {
        if (frame == 0) DrawBitmapAsset(ghost->assets[8], sprite->position, sprite->size);
        else DrawBitmapAsset(ghost->assets[9], sprite->position, sprite->size);
        return;
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

static Vector2 _FindFleePosition(Sprite *map) {
    Sprite *pacMan = FindGameSpriteByName(GetCurrentScene(), "PacMan");
    TiledMapAsset *asset = map->property;
    Vector2 resPos = ZERO_VECTOR;
    double resDist = -1.;
    for (int i = 0; i < asset->width; i++) {
        for (int j = 0; j < asset->height; j++) {
            if (!IsTileWalkable(map, i, j)) continue;
            Vector2 tilePos = GetTilePosition(map, i, j);
            double dist = VLengthSquared(VSubtract(pacMan->position, tilePos));
            if (dist > resDist) {
                resPos = tilePos;
                resDist = dist;
            }
        }
    }
    return resPos;
}

static void _UpdatePath(Sprite *this) {
    Ghost *ghost = this->property;
    if (ghost->chasedAfter) {
        this->navAgent.targetType = POS_TARGET;
        this->navAgent.target.position = _FindFleePosition(FindGameSpriteByName(GetCurrentScene(), "Map"));
    } else if (this->navAgent.targetType == POS_TARGET) {
        this->navAgent.targetType = SPRITE_TARGET;
        this->navAgent.target.sprite = FindGameSpriteByName(GetCurrentScene(), "PacMan");
    }
    UpdatePath(GetCurrentScene(), this);
}

static void _Collide(Sprite *this, int id, Sprite *other) {
    if (other->name && !strcmp(other->name, "PacMan")) {

    }
}

Sprite *ConstructGhostBlinkySprite(Sprite *target) {
    Sprite *obj = ConstructSprite((Vector2) {6.45, 6}, (Vector2) {0.3, 0.3}, ZERO_VECTOR);
    RegisterBoxCollider(obj, 0, true, obj->size, ZERO_VECTOR);
    RegisterTimer(obj, 500, _UpdatePath);
    SetNavTargetSprite(obj, target);

    Animator *animator = ConstructAnimator(2);
    animator->Animate = _Animate;
    for (int i = 0; i < 2; i++)animator->intervals[i] = 200;

    obj->name = "GhostBlinky";
    obj->hasAnimation = true;
    obj->renderer.animator = animator;
    obj->property = _ConstructGhost();
    obj->Collide = _Collide;
    _objCount++;
    return obj;
}
