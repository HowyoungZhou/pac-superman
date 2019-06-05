#include <sprite.h>
#include "ghost_sprite.h"
#include "ghost_blinky_sprite.h"

Sprite *ConstructGhostBlinkySprite(Vector2 position, Vector2 size) {
    Sprite *obj = ConstructGhostSprite(position, size, "GhostBlinky");
    Ghost *ghost = obj->property;
    ghost->assets[0] = LoadBitmapAsset("ghost/blinky/blinky-right1.bmp");
    ghost->assets[1] = LoadBitmapAsset("ghost/blinky/blinky-right2.bmp");
    ghost->assets[2] = LoadBitmapAsset("ghost/blinky/blinky-up1.bmp");
    ghost->assets[3] = LoadBitmapAsset("ghost/blinky/blinky-up2.bmp");
    ghost->assets[4] = LoadBitmapAsset("ghost/blinky/blinky-left1.bmp");
    ghost->assets[5] = LoadBitmapAsset("ghost/blinky/blinky-left2.bmp");
    ghost->assets[6] = LoadBitmapAsset("ghost/blinky/blinky-down1.bmp");
    ghost->assets[7] = LoadBitmapAsset("ghost/blinky/blinky-down2.bmp");
    return obj;
}