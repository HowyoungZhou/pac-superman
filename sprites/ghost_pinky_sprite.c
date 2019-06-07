#include <sprite.h>
#include <game_controller.h>
#include <scene.h>
#include <engine.h>
#include <game_scene.h>
#include "ghost_sprite.h"
#include "ghost_pinky_sprite.h"
#include "map_sprite.h"

#define AMBUSH_DIST 4
#define DELAY 1000

static void _Go(Sprite *this);

static Vector2 _FindFleePosition(Sprite *map);

static void _UpdatePath(Sprite *this);

static Vector2 _FindFleePosition(Sprite *map) {
    Sprite *pacMan = FindGameSpriteByName(GetCurrentScene(), "PacMan");
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

static inline void _UpdateTarget(Sprite *this) {
    Scene *current = GetCurrentScene();
    Sprite *pacman = FindGameSpriteByName(GetCurrentScene(), "PacMan");
    Sprite *map = GetCurrentMap();
    double tileLength = GetTileSize(map).x;
    Vector2 ambushPos = VAdd(pacman->position,
                             VMultiply(AMBUSH_DIST * tileLength, VNormalize(pacman->velocity)));
    SetNavTargetPosition(this, ambushPos);
    if (!UpdatePath(current, this)) {
        SetNavTargetSprite(this, pacman);
        UpdatePath(current, this);
    }
}

static void _UpdatePath(Sprite *this) {
    Ghost *ghost = this->property;
    switch (ghost->state) {
        case CHASING:
            this->navAgent.speed = GetGameObjectOption().ghostChasingSpeed;
            _UpdateTarget(this);
            break;
        case CHASED_AFTER:
            this->navAgent.speed = GetGameObjectOption().ghostChasedSpeed;
            SetNavTargetPosition(this, _FindFleePosition(GetCurrentMap()));
            UpdatePath(GetCurrentScene(), this);
            break;
        default:
            break;
    }
}

static void _Go(Sprite *this) {
    _UpdatePath(this);
    RegisterTimer(this, GetGameObjectOption().ghostPathfindingInterval, _UpdatePath);
    DisableTimer(this, _Go);
}

Sprite *ConstructGhostPinkySprite(Vector2 position, Vector2 size) {
    Sprite *obj = ConstructGhostSprite(position, size, "Pinky");
    Ghost *ghost = obj->property;
    ghost->assets[0] = LoadBitmapAsset("ghost/pinky/pinky-right1.bmp");
    ghost->assets[1] = LoadBitmapAsset("ghost/pinky/pinky-right2.bmp");
    ghost->assets[2] = LoadBitmapAsset("ghost/pinky/pinky-up1.bmp");
    ghost->assets[3] = LoadBitmapAsset("ghost/pinky/pinky-up2.bmp");
    ghost->assets[4] = LoadBitmapAsset("ghost/pinky/pinky-left1.bmp");
    ghost->assets[5] = LoadBitmapAsset("ghost/pinky/pinky-left2.bmp");
    ghost->assets[6] = LoadBitmapAsset("ghost/pinky/pinky-down1.bmp");
    ghost->assets[7] = LoadBitmapAsset("ghost/pinky/pinky-down2.bmp");

    RegisterTimer(obj, DELAY, _Go);
    return obj;
}

void ResetPinky(Sprite *this) {
    ResetGhost(this);
    RegisterTimer(this, DELAY, _Go);
}
