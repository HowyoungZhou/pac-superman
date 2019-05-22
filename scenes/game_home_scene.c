#include <scene.h>
#include <example_controllable_sprite.h>
#include <pellet.h>
#include <pacman_sprite.h>
#include <button.h>
#include <game_menu.h>
#include <vector2.h>
#include <engine.h>
#include "graphics.h"
#include <example_bitmap_sprite.h>
#include "game_home_scene.h"
#include "image.h"

static double cx,cy;

void _Swift(){

}

void _Home_Initialize(Scene *scene) {

    cx = GetWindowWidth();
    cy = GetWindowHeight();
    AddUISprite(scene, ConstructButtonSprite(1, (Vector2) {cx/2-1, cy/2-0.3}, (Vector2) {2, 0.6}, "Start",_Swift));
    AddUISprite(scene, ConstructButtonSprite(2, (Vector2) {cx/2-1, cy/2-1.2}, (Vector2) {2, 0.6}, "Ranking", _Swift));
    AddUISprite(scene, ConstructButtonSprite(3, (Vector2) {cx/2-1, cy/2-2.1}, (Vector2) {2, 0.6}, "Instruction", _Swift));
    AddUISprite(scene, ConstructGameMenuSprite());
    AddUISprite(scene,ConstructImageSprite((Vector2){cx/2-1.25,cy/2+0.6},(Vector2){2.5,2},"Home/logo.bmp"));
}

Scene *ConstructHomeScene() {
    Scene *obj = ConstructScene(_Home_Initialize);
    return obj;
}