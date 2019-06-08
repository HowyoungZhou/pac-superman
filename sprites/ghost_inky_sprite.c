#include <sprite.h>
#include <game_controller.h>
#include <scene.h>
#include <engine.h>
#include <game_scene.h>
#include <autonav.h>
#include "ghost_sprite.h"
#include "ghost_inky_sprite.h"
#include "map_sprite.h"

#define DELAY 2000

static void _Go(Sprite *this);

static void _UpdatePath(Sprite *this);

static inline void _UpdateTarget(Sprite *this) {
    Scene *current = GetCurrentScene();
    Sprite *blinky = GetCurrentHeros().blinky;
    Sprite *pacman = GetCurrentHeros().pacman;
    Vector2 target = VAdd(pacman->position, VSubtract(pacman->position, blinky->position));
    SetNavTargetPosition(this, target);
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
            SetNavTargetPosition(this, GetFleePosition());
            UpdatePath(GetCurrentScene(), this);
            break;
        default:
            break;
    }
}

static void _Go(Sprite *this) {
    _UpdatePath(this);
    EnableTimer(this, _UpdatePath);
    DisableTimer(this, _Go);
}

Sprite *ConstructGhostInkySprite(Vector2 position, Vector2 size) {
    Sprite *obj = ConstructGhostSprite(position, size, "Inky");
    Ghost *ghost = obj->property;
    ghost->assets[0] = LoadBitmapAsset("ghost/inky/inky-right1.bmp");
    ghost->assets[1] = LoadBitmapAsset("ghost/inky/inky-right2.bmp");
    ghost->assets[2] = LoadBitmapAsset("ghost/inky/inky-up1.bmp");
    ghost->assets[3] = LoadBitmapAsset("ghost/inky/inky-up2.bmp");
    ghost->assets[4] = LoadBitmapAsset("ghost/inky/inky-left1.bmp");
    ghost->assets[5] = LoadBitmapAsset("ghost/inky/inky-left2.bmp");
    ghost->assets[6] = LoadBitmapAsset("ghost/inky/inky-down1.bmp");
    ghost->assets[7] = LoadBitmapAsset("ghost/inky/inky-down2.bmp");

    RegisterTimer(obj, DELAY, _Go, true);
    RegisterTimer(obj, GetGameObjectOption().ghostPathfindingInterval, _UpdatePath, false);
    return obj;
}

void ResetInky(Sprite *this) {
    ResetGhost(this);
    EnableTimer(this, _Go);
}
