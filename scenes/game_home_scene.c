#include <scene.h>
#include <button.h>
#include <game_menu.h>
#include <vector2.h>
#include <engine.h>
#include "graphics.h"
#include "game_home_scene.h"
#include "image.h"
#include <game_level_scene.h>
#include <game_ranking_list_scene.h>
#include <game_instruction_scene.h>
#include <about_scene.h>

static double cx,cy;

void _HomeToLevel(){
    ReplaceScene(ConstructLevelScene());
}

void _HomeToRanking(){
    PushScene(ConstructRankingListScene());
}

void _HomeToIns(){
    PushScene(ConstructInstructionScene());
}

void _HomeToAbout(){
    PushScene(ConstructAboutScene());
}

void _Home_Initialize(Scene *scene) {

    cx = GetWindowWidth();
    cy = GetWindowHeight();
    AddUISprite(scene, ConstructButtonSprite(1, (Vector2) {cx/2-1, cy/2-1.4}, (Vector2) {2, 0.4}, "Start",_HomeToLevel));
    AddUISprite(scene, ConstructButtonSprite(2, (Vector2) {cx/2-1, cy/2-2}, (Vector2) {2, 0.4}, "Ranking", _HomeToRanking));
    AddUISprite(scene, ConstructButtonSprite(3, (Vector2) {cx/2-1, cy/2-2.6}, (Vector2) {2, 0.4}, "Instruction", _HomeToIns));
    AddUISprite(scene, ConstructButtonSprite(4, (Vector2) {cx/2-1, cy/2-3.2}, (Vector2) {2, 0.4}, "About", _HomeToAbout));
    AddUISprite(scene,ConstructImageSprite((Vector2){cx/2-2.5,cy/2-0.9},(Vector2){5,4.5},"Home/logo7.bmp"));

    /*田字形布局
    AddUISprite(scene, ConstructButtonSprite(1, (Vector2) {cx/2-2.2, cy/2-2.6}, (Vector2) {2, 0.4}, "Start",_HomeToLevel));
    AddUISprite(scene, ConstructButtonSprite(2, (Vector2) {cx/2-2.2, cy/2-3.2}, (Vector2) {2, 0.4}, "Ranking", _HomeToRanking));
    AddUISprite(scene, ConstructButtonSprite(3, (Vector2) {cx/2+0.2, cy/2-2.6}, (Vector2) {2, 0.4}, "Instruction", _HomeToIns));
    AddUISprite(scene, ConstructButtonSprite(4, (Vector2) {cx/2+0.2, cy/2-3.2}, (Vector2) {2, 0.4}, "About", _HomeToAbout));
    AddUISprite(scene,ConstructImageSprite((Vector2){cx/2-3,cy/2-1.8},(Vector2){6,5},"Home/logo7.bmp"));
    */

    /*左右布局
    AddUISprite(scene, ConstructButtonSprite(1, (Vector2) {cx/2+2, cy/2+1.8}, (Vector2) {2, 0.7}, "Start",_HomeToLevel));
    AddUISprite(scene, ConstructButtonSprite(2, (Vector2) {cx/2+2, cy/2+0.5}, (Vector2) {2, 0.7}, "Ranking", _HomeToRanking));
    AddUISprite(scene, ConstructButtonSprite(3, (Vector2) {cx/2+2, cy/2-0.8}, (Vector2) {2, 0.7}, "Instruction", _HomeToIns));
    AddUISprite(scene, ConstructButtonSprite(4, (Vector2) {cx/2+2, cy/2-2.1}, (Vector2) {2, 0.7}, "About", _HomeToAbout));
    AddUISprite(scene,ConstructImageSprite((Vector2){cx/2-4.5,cy/2-2.5},(Vector2){6.5,5.4},"Home/logo7.bmp"));
    */
}

Scene *ConstructHomeScene() {
    Scene *obj = ConstructScene(_Home_Initialize);
    return obj;
}