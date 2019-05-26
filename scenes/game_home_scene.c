#include <scene.h>
#include <button.h>
#include <game_menu.h>
#include <vector2.h>
#include <engine.h>
#include "graphics.h"
#include <example_bitmap_sprite.h>
#include "game_home_scene.h"
#include "image.h"
#include <game_level_scene.h>
#include <game_RankingList_scene.h>
#include <game_instruction_scene.h>

static double cx,cy;

void _SwiftToLevel(){
    ReplaceScene(ConstructLevelScene());
}

void _SwiftToRanking(){
    ReplaceScene(ConstructRankingListScene());
}

void _SwiftToIns(){
    ReplaceScene(ConstructInstructionScene());
}

void _Home_Initialize(Scene *scene) {

    cx = GetWindowWidth();
    cy = GetWindowHeight();
    AddUISprite(scene, ConstructButtonSprite(1, (Vector2) {cx/2-1, cy/2-0.3}, (Vector2) {2, 0.6}, "Start",_SwiftToLevel));
    AddUISprite(scene, ConstructButtonSprite(2, (Vector2) {cx/2-1, cy/2-1.2}, (Vector2) {2, 0.6}, "Ranking", _SwiftToRanking));
    AddUISprite(scene, ConstructButtonSprite(3, (Vector2) {cx/2-1, cy/2-2.1}, (Vector2) {2, 0.6}, "Instruction", _SwiftToIns));
    AddUISprite(scene, ConstructGameMenuSprite());
    AddUISprite(scene,ConstructImageSprite((Vector2){cx/2-1.25,cy/2+0.6},(Vector2){2.5,2},"Home/logoa.bmp"));
}

Scene *ConstructHomeScene() {
    Scene *obj = ConstructScene(_Home_Initialize);
    return obj;
}