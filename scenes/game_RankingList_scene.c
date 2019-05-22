#include <scene.h>
#include <example_controllable_sprite.h>
#include <pellet.h>
#include <pacman_sprite.h>
#include <button.h>
#include <game_menu.h>
#include <vector2.h>
#include <engine.h>
#include <example_bitmap_sprite.h>
#include <image.h>
#include <graphics.h>
#include "game_RankingList_scene.h"

static double cx,cy;

void _RankingList_Initialize(Scene *scene) {

    cx = GetWindowWidth();
    cy = GetWindowHeight();

    AddUISprite(scene, ConstructImageSprite((Vector2){cx/2-3,cy*0.7},(Vector2){6,2},"RankingList/RL_Title1.bmp"));
    AddUISprite(scene, ConstructImageSprite((Vector2){cx/2-3,cy*0.6},(Vector2){1,1},"RankingList/Number1.bmp"));
}

Scene *ConstructRankingListScene() {
    Scene *obj = ConstructScene(_RankingList_Initialize);
    return obj;
}