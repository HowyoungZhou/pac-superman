#include <scene.h>
#include <button.h>
#include <game_menu.h>
#include <vector2.h>
#include <engine.h>
#include "graphics.h"
#include "game_home_scene.h"
#include "image.h"
#include <game_level_scene.h>
#include <game_RankingList_scene.h>
#include <game_instruction_scene.h>
#include <about_scene.h>

static double cx,cy;

void _HomeToLevel(){
    ReplaceScene(ConstructLevelScene());
}

void _HomeToRanking(){
    ReplaceScene(ConstructRankingListScene());
}

void _HomeToIns(){
    ReplaceScene(ConstructInstructionScene());
}

void _HomeToAbout(){
    ReplaceScene(ConstructAboutScene());
}

void _Home_Initialize(Scene *scene) {

    cx = GetWindowWidth();
    cy = GetWindowHeight();
    AddUISprite(scene, ConstructButtonSprite(1, (Vector2) {cx/2-1, cy/2-0.2}, (Vector2) {2, 0.5}, "Start",_HomeToLevel));
    AddUISprite(scene, ConstructButtonSprite(2, (Vector2) {cx/2-1, cy/2-1}, (Vector2) {2, 0.5}, "Ranking", _HomeToRanking));
    AddUISprite(scene, ConstructButtonSprite(3, (Vector2) {cx/2-1, cy/2-1.8}, (Vector2) {2, 0.5}, "Instruction", _HomeToIns));
    AddUISprite(scene, ConstructButtonSprite(4, (Vector2) {cx/2-1, cy/2-2.6}, (Vector2) {2, 0.5}, "About", _HomeToAbout));
    AddUISprite(scene, ConstructGameMenuSprite());
    AddUISprite(scene,ConstructImageSprite((Vector2){cx/2-1.25,cy/2+0.6},(Vector2){2.5,2},"Home/logoa.bmp"));
}

Scene *ConstructHomeScene() {
    Scene *obj = ConstructScene(_Home_Initialize);
    return obj;
}