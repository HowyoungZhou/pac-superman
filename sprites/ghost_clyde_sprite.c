#include <math.h>
#include <sprite.h>
#include <game_controller.h>
#include <scene.h>
#include <engine.h>
#include <game_scene.h>
#include "ghost_sprite.h"
#include "ghost_clyde_sprite.h"
#include "map_sprite.h"

#define CLOSE_DISTANCE 8
#define DELAY 3000

static void _Go(Sprite *this);

static Vector2 _FindFleePosition(Sprite *map);

static inline void _UpdateTarget(Sprite *this);

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
    Ghost *ghost = this->property;
    Sprite *pacman = FindGameSpriteByName(GetCurrentScene(), "PacMan");
    double tileWidth = GetTileSize(GetCurrentMap()).x;
    if (VLength(VSubtract(pacman->position, this->position)) < CLOSE_DISTANCE * tileWidth) {
        SetNavTargetPosition(this, ghost->initPos);
    } else SetNavTargetSprite(this, pacman);
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
            break;
        default:
            break;
    }
    UpdatePath(GetCurrentScene(), this);
}

static void _Go(Sprite *this) {
    _UpdatePath(this);
    RegisterTimer(this, GetGameObjectOption().ghostPathfindingInterval, _UpdatePath);
    DisableTimer(this, _Go);
}

Sprite *ConstructGhostClydeSprite(Vector2 position, Vector2 size) {
    Sprite *obj = ConstructGhostSprite(position, size, "Clyde");
    Ghost *ghost = obj->property;
    ghost->assets[0] = LoadBitmapAsset("ghost/clyde/clyde-right1.bmp");
    ghost->assets[1] = LoadBitmapAsset("ghost/clyde/clyde-right2.bmp");
    ghost->assets[2] = LoadBitmapAsset("ghost/clyde/clyde-up1.bmp");
    ghost->assets[3] = LoadBitmapAsset("ghost/clyde/clyde-up2.bmp");
    ghost->assets[4] = LoadBitmapAsset("ghost/clyde/clyde-left1.bmp");
    ghost->assets[5] = LoadBitmapAsset("ghost/clyde/clyde-left2.bmp");
    ghost->assets[6] = LoadBitmapAsset("ghost/clyde/clyde-down1.bmp");
    ghost->assets[7] = LoadBitmapAsset("ghost/clyde/clyde-down2.bmp");

    RegisterTimer(obj, DELAY, _Go);
    return obj;
}

void ResetClyde(Sprite *this) {
    ResetGhost(this);
    RegisterTimer(this, DELAY, _Go);
}
