#include <scene.h>
#include <button.h>
#include <game_menu.h>
#include <vector2.h>
#include <engine.h>
#include <ghost_blinky_sprite.h>
#include <image.h>
#include <graphics.h>
#include "game_level_scene.h"
#include "game_controller.h"
#include <game_scene.h>
#include <imgui.h>
#include <end_game_box.h>
#include <extgraph.h>

#define DEFAULT_MAP "maps/classic"

static double cx, cy;

static Scene *_CurrentScene;

void _Easy() {
    SetDifficulty(EASY);
    ReplaceScene(ConstructGameScene(DEFAULT_MAP));
}

void _Normal() {
    SetDifficulty(NORMAL);
    ReplaceScene(ConstructGameScene(DEFAULT_MAP));
}

void _Hard() {
    SetDifficulty(HARD);
    ReplaceScene(ConstructGameScene(DEFAULT_MAP));
}

void _Level_Initialize(Scene *scene) {

    cx = GetWindowWidth();
    cy = GetWindowHeight();
    _CurrentScene = scene;
    AddUISprite(scene,
                ConstructButtonSprite(1, (Vector2) {cx / 2 - 2.5, cy / 2 - 0.75}, (Vector2) {1, 1.5}, "EASY", _Easy));
    AddUISprite(scene, ConstructButtonSprite(2, (Vector2) {cx / 2 - 0.5, cy / 2 - 0.75}, (Vector2) {1, 1.5}, "NORMAL",
                                             _Normal));
    AddUISprite(scene,
                ConstructButtonSprite(3, (Vector2) {cx / 2 + 1.5, cy / 2 - 0.75}, (Vector2) {1, 1.5}, "HARD", _Hard));
    AddUISprite(scene, ConstructImageSprite((Vector2) {cx / 2 - 3, cy * 0.7}, (Vector2) {6, 2},
                                            "LevelSelection/LS_Title.bmp"));

}

Scene *ConstructLevelScene() {
    Scene *obj = ConstructScene(_Level_Initialize);
    return obj;
}