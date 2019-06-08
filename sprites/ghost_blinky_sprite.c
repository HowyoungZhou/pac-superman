#include <sprite.h>
#include <game_controller.h>
#include <scene.h>
#include <engine.h>
#include <game_scene.h>
#include <dynamic_array.h>
#include "ghost_sprite.h"
#include "ghost_blinky_sprite.h"
#include "map_sprite.h"

#define DELAY 0

static void _UpdatePath(Sprite *this);

static void _Go(Sprite *this);

static void _UpdatePath(Sprite *this) {
    Ghost *ghost = this->property;
    switch (ghost->state) {
        case CHASING:
            this->navAgent.speed = GetGameObjectOption().ghostChasingSpeed;
            SetNavTargetSprite(this, GetCurrentHeros()->pacman);
            break;
        case CHASED_AFTER:
            this->navAgent.speed = GetGameObjectOption().ghostChasedSpeed;
            SetNavTargetPosition(this, GetFleePosition());
            break;
        default:
            break;
    }
    UpdatePath(GetCurrentScene(), this);
}

static void _Go(Sprite *this) {
    _UpdatePath(this);
    EnableTimer(this, _UpdatePath);
    DisableTimer(this, _Go);
}

Sprite *ConstructGhostBlinkySprite(Vector2 position, Vector2 size) {
    Sprite *obj = ConstructGhostSprite(position, size, "Blinky");
    Ghost *ghost = obj->property;
    ghost->assets[0] = LoadBitmapAsset("ghost/blinky/blinky-right1.bmp");
    ghost->assets[1] = LoadBitmapAsset("ghost/blinky/blinky-right2.bmp");
    ghost->assets[2] = LoadBitmapAsset("ghost/blinky/blinky-up1.bmp");
    ghost->assets[3] = LoadBitmapAsset("ghost/blinky/blinky-up2.bmp");
    ghost->assets[4] = LoadBitmapAsset("ghost/blinky/blinky-left1.bmp");
    ghost->assets[5] = LoadBitmapAsset("ghost/blinky/blinky-left2.bmp");
    ghost->assets[6] = LoadBitmapAsset("ghost/blinky/blinky-down1.bmp");
    ghost->assets[7] = LoadBitmapAsset("ghost/blinky/blinky-down2.bmp");

    RegisterTimer(obj, DELAY, _Go, true);
    RegisterTimer(obj, GetGameObjectOption().ghostPathfindingInterval, _UpdatePath, false);

    GetCurrentHeros()->blinky = obj;
    return obj;
}

void ResetBlinky(Sprite *this) {
    ResetGhost(this);
    EnableTimer(this, _Go);
}
