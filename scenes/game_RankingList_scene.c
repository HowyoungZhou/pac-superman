#include <scene.h>
#include <button.h>
#include <game_menu.h>
#include <vector2.h>
#include <engine.h>
#include <ghost_blinky_sprite.h>
#include <image.h>
#include <graphics.h>
#include "game_RankingList_scene.h"
#include <game_home_scene.h>
#include <rank_display.h>

static double cx, cy;

void _RankToHome() {
    PopScene();
}

void _RankingList_Initialize(Scene *scene) {

    cx = GetWindowWidth();
    cy = GetWindowHeight();

    AddUISprite(scene, ConstructButtonSprite(1, (Vector2) {0.2, 0.2}, (Vector2) {0.55, 0.55}, "BACK", _RankToHome));
    AddUISprite(scene, ConstructImageSprite((Vector2){cx/2-3,cy*0.7},(Vector2){6,2},"RankingList/RL_Title1.bmp"));
    AddUISprite(scene, ConstructImageSprite((Vector2){cx/2-3,cy*0.15},(Vector2){6,4.2},"RankingList/Chart.bmp"));
    AddUISprite(scene, ConstructRankDisplaySprite());
}

Scene *ConstructRankingListScene() {
    Scene *obj = ConstructScene(_RankingList_Initialize);
    return obj;
}