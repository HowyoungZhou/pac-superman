#include <sprite.h>
#include <assets.h>
#include <extgraph.h>
#include <controller.h>
#include <exception.h>
#include <engine.h>
#include <game_controller.h>
#include <autonav.h>
#include "map_sprite.h"
#include <ghost_sprite.h>

#define EYES_SPEED 3

static inline Ghost *_ConstructGhost(Vector2 initPos);

static inline void _DestructGhost(Ghost *this);

static inline void _LoadPublicAssets();

static inline void _FreePublicAssets();

static void _Animate(Animator *this, Sprite *sprite, Frame frame);

static void _Destruct(Sprite *this);

static void _Collide(Sprite *this, int id, Sprite *other);

static void _Update(Sprite *this, double interval);

static int _objCount = 0;
static BitmapAsset *_pubicAssets[6];

static inline Ghost *_ConstructGhost(Vector2 initPos) {
    Ghost *obj = malloc(sizeof(Ghost));
    obj->initPos = initPos;
    obj->lookingAt = DOWN;
    obj->state = CHASING;
    return obj;
}

static inline void _DestructGhost(Ghost *this) {
    for (int i = 0; i < sizeof(this->assets) / sizeof(BitmapAsset *); i++) {
        FreeBitmapAsset(this->assets[i]);
    }
    free(this);
}

static inline void _LoadPublicAssets() {
    _pubicAssets[0] = LoadBitmapAsset("ghost/flash/flash1.bmp");
    _pubicAssets[1] = LoadBitmapAsset("ghost/flash/flash2.bmp");
    _pubicAssets[2] = LoadBitmapAsset("ghost/eyes/eyes-right.bmp");
    _pubicAssets[3] = LoadBitmapAsset("ghost/eyes/eyes-up.bmp");
    _pubicAssets[4] = LoadBitmapAsset("ghost/eyes/eyes-left.bmp");
    _pubicAssets[5] = LoadBitmapAsset("ghost/eyes/eyes-down.bmp");
}

static inline void _FreePublicAssets() {
    for (int i = 0; i < sizeof(_pubicAssets) / sizeof(BitmapAsset *); i++) {
        FreeBitmapAsset(_pubicAssets[i]);
    }
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

    switch (ghost->state) {
        case CHASED_AFTER:
            if (frame == 0) DrawBitmapAsset(_pubicAssets[0], sprite->position, sprite->size);
            else DrawBitmapAsset(_pubicAssets[1], sprite->position, sprite->size);
            break;
        case CHASING:
        case EATEN:
            switch (ghost->lookingAt) {
                case RIGHT:
                    if (ghost->state == EATEN) DrawBitmapAsset(_pubicAssets[2], sprite->position, sprite->size);
                    else if (frame == 0) DrawBitmapAsset(ghost->assets[0], sprite->position, sprite->size);
                    else DrawBitmapAsset(ghost->assets[1], sprite->position, sprite->size);
                    break;
                case UP:
                    if (ghost->state == EATEN) DrawBitmapAsset(_pubicAssets[3], sprite->position, sprite->size);
                    else if (frame == 0) DrawBitmapAsset(ghost->assets[2], sprite->position, sprite->size);
                    else DrawBitmapAsset(ghost->assets[3], sprite->position, sprite->size);
                    break;
                case LEFT:
                    if (ghost->state == EATEN) DrawBitmapAsset(_pubicAssets[4], sprite->position, sprite->size);
                    else if (frame == 0) DrawBitmapAsset(ghost->assets[4], sprite->position, sprite->size);
                    else DrawBitmapAsset(ghost->assets[5], sprite->position, sprite->size);
                    break;
                case DOWN:
                    if (ghost->state == EATEN) DrawBitmapAsset(_pubicAssets[5], sprite->position, sprite->size);
                    else if (frame == 0) DrawBitmapAsset(ghost->assets[6], sprite->position, sprite->size);
                    else DrawBitmapAsset(ghost->assets[7], sprite->position, sprite->size);
                    break;
            }
    }
}

static void _Destruct(Sprite *this) {
    _DestructGhost(this->property);
    _objCount--;
    if (_objCount == 0) _FreePublicAssets();
    DestructSprite(this);
}

static void _Collide(Sprite *this, int id, Sprite *other) {
    if (!other->name || strcmp(other->name, "PacMan") != 0) return;
    Ghost *ghost = this->property;
    switch (ghost->state) {
        case CHASING:
            break;
        case CHASED_AFTER:
            ghost->state = EATEN;
            this->navAgent.speed = EYES_SPEED;
            SetNavTargetPosition(this, ghost->initPos);
            UpdatePath(GetCurrentScene(), this);
            break;
        default:
            break;
    }
}

static void _Update(Sprite *this, double interval) {
    Ghost *ghost = this->property;
    if (ghost->state == EATEN && !this->navAgent.path) {
        ghost->state = CHASING;
        this->navAgent.speed = GetGameObjectOption().ghostChasingSpeed;
    }
}

Sprite *ConstructGhostSprite(Vector2 position, Vector2 size, string name) {
    Sprite *obj = ConstructSprite(position, size, ZERO_VECTOR);
    RegisterBoxCollider(obj, 0, true, obj->size, ZERO_VECTOR);

    Animator *animator = ConstructAnimator(2);
    animator->Animate = _Animate;
    for (int i = 0; i < 2; i++)animator->intervals[i] = 200;

    obj->name = name;
    obj->hasAnimation = true;
    obj->renderer.animator = animator;
    obj->property = _ConstructGhost(position);
    obj->Collide = _Collide;
    obj->Update = _Update;
    if (_objCount == 0) _LoadPublicAssets();
    _objCount++;
    return obj;
}
