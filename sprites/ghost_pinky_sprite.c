#include <sprite.h>
#include <game_controller.h>
#include <scene.h>
#include <engine.h>
#include "ghost_sprite.h"
#include "ghost_pinky_sprite.h"
#include "map_sprite.h"

#define DELAY 1000

static void _Go(Sprite *this);

static Vector2 _FindFleePosition(Sprite *map);

static void _UpdatePath(Sprite *this);

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
    switch (ghost->state) {
        case CHASING:
            this->navAgent.speed = GetGameObjectOption().ghostChasingSpeed;
            SetNavTargetSprite(this, FindGameSpriteByName(GetCurrentScene(), "PacMan"));
            break;
        case CHASED_AFTER:
            this->navAgent.speed = GetGameObjectOption().ghostChasedSpeed;
            SetNavTargetPosition(this, _FindFleePosition(FindGameSpriteByName(GetCurrentScene(), "Map")));
            break;
        default:
            break;
    }
    UpdatePath(GetCurrentScene(), this);
}

static void _Go(Sprite *this) {
    _UpdatePath(this);
    RegisterTimer(this, PATH_UPDATE_INTERVAL, _UpdatePath);
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
