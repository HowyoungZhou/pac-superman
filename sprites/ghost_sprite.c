#include <sprite.h>
#include <assets.h>
#include <extgraph.h>
#include <controller.h>
#include <exception.h>
#include <engine.h>
#include <game_controller.h>
#include <autonav.h>
#include "map_sprite.h"
#include "pacman_sprite.h"
#include <ghost_sprite.h>
#include <game_scene.h>
#include <time.h>

#define INIT_TIME -1
#define FLASH_COUNTDOWN 3000
#define GHOST_SCORE 200
#define EYES_SPEED 3

static inline Ghost *_ConstructGhost(Vector2 initPos);

static inline void _DestructGhost(Ghost *this);

static inline void _LoadPublicAssets();

static inline void _FreePublicAssets();

static void _Animate(Animator *this, Sprite *sprite, Frame frame);

static void _Destruct(Sprite *this);

static void _Collide(Sprite *this, int id, Sprite *other);

static void _Update(Sprite *this, double interval);

static inline Vector2 _FindFleePosition(Sprite *map);

static int _objCount = 0;
static BitmapAsset *_pubicAssets[6];
static clock_t _lastUpdate = INIT_TIME;
static Vector2 _fleePos = ZERO_VECTOR;

static inline Ghost *_ConstructGhost(Vector2 initPos) {
    Ghost *obj = malloc(sizeof(Ghost));
    obj->initPos = initPos;
    obj->lookingAt = DOWN;
    obj->state = CHASING;
    obj->chasedCountDown = 0;
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
            if (ghost->chasedCountDown <= FLASH_COUNTDOWN) {
                if (frame == 0) DrawBitmapAsset(_pubicAssets[0], sprite->position, sprite->size);
                else DrawBitmapAsset(_pubicAssets[1], sprite->position, sprite->size);
            } else {
                DrawBitmapAsset(_pubicAssets[0], sprite->position, sprite->size);
            }
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
    other->velocity = ZERO_VECTOR;
    if (!other->name || strcmp(other->name, "PacMan") != 0) return;
    Ghost *ghost = this->property;
    switch (ghost->state) {
        case CHASING:
            ChangeLife(-1);
            if (GetLife() == 0) {
                //TODO: 显示游戏失败提示
            } else {
                RevivePacMan();
            }
            break;
        case CHASED_AFTER:
            ChangeScore(GHOST_SCORE);
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
    switch (ghost->state) {
        case CHASED_AFTER:
            ghost->chasedCountDown -= interval;
            if (ghost->chasedCountDown <= 0) {
                ghost->state = CHASING;
                this->navAgent.speed = GetGameObjectOption().ghostChasingSpeed;
            }
            break;
        case EATEN:
            if (!this->navAgent.path) {
                ghost->state = CHASING;
                this->navAgent.speed = GetGameObjectOption().ghostChasingSpeed;
            }
            break;
        default:
            break;
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
    _lastUpdate = INIT_TIME;
    return obj;
}

void ResetGhost(Sprite *this) {
    Ghost *ghost = this->property;
    this->position = ghost->initPos;
    this->velocity = ZERO_VECTOR;
    DisableTimers(this);
    FreePath(this->navAgent.path);
    this->navAgent.path = NULL;
    ghost->state = CHASING;
    ghost->lookingAt = UP;
}

static inline Vector2 _FindFleePosition(Sprite *map) {
    Sprite *pacMan = GetCurrentHeros().pacman;
    DynamicArray walkableTiles = GetAllWalkableTiles();
    Vector2 resPos = ZERO_VECTOR;
    double resDist = -1.;
    for (int i = 0; i < walkableTiles.length; i++) {
        Vector2 tilePos = *ArrayGetElement(walkableTiles, Vector2*, i);
        double dist = VLengthSquared(VSubtract(pacMan->position, tilePos));
        if (dist > resDist) {
            resPos = tilePos;
            resDist = dist;
        }
    }
    return resPos;
}

Vector2 GetFleePosition() {
    // 检查上次更新时间是否已超出了更新间隔
    if (_lastUpdate == INIT_TIME ||
        (double) (clock() - _lastUpdate) / CLOCKS_PER_SEC * 1000 > GetGameObjectOption().ghostPathfindingInterval)
        _fleePos = _FindFleePosition(GetCurrentHeros().map);
    return _fleePos;
}
