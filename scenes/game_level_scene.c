#include <scene.h>
#include <button.h>
#include <game_menu.h>
#include <vector2.h>
#include <engine.h>
#include <example_bitmap_sprite.h>
#include <image.h>
#include <graphics.h>
#include "game_level_scene.h"
#include <game_scene.h>

static double cx,cy;

void _Easy(){
    ReplaceScene(ConstructGameScene());
}

void _Normal(){
    ReplaceScene(ConstructGameScene());
}

void _Hard(){
    ReplaceScene(ConstructGameScene());
}

void _Level_Initialize(Scene *scene) {

    cx = GetWindowWidth();
    cy = GetWindowHeight();
    AddUISprite(scene, ConstructButtonSprite(1, (Vector2) {cx/2-2.5, cy/2-0.75}, (Vector2) {1, 1.5}, "EASY", _Easy));
    AddUISprite(scene, ConstructButtonSprite(2, (Vector2) {cx/2-0.5, cy/2-0.75}, (Vector2) {1, 1.5}, "NORMAL",_Normal));
    AddUISprite(scene, ConstructButtonSprite(3, (Vector2) {cx/2+1.5, cy/2-0.75}, (Vector2) {1, 1.5}, "HARD", _Hard));
    AddUISprite(scene, ConstructImageSprite((Vector2){cx/2-3,cy*0.7},(Vector2){6,2},"LevelSelection/LS_Title.bmp"));

}

Scene *ConstructLevelScene() {
    Scene *obj = ConstructScene(_Level_Initialize);
    return obj;
}