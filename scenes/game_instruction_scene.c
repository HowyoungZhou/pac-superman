#include <scene.h>
#include <button.h>
#include <game_menu.h>
#include <vector2.h>
#include <engine.h>
#include <ghost_blinky_sprite.h>
#include <image.h>
#include <graphics.h>
#include <game_home_scene.h>
#include "game_instruction_scene.h"

static double cx,cy;

void _InsToHome(){
    ReplaceScene(ConstructHomeScene());
}

void _Instruction_Initialize(Scene *scene) {

    cx = GetWindowWidth();
    cy = GetWindowHeight();

    AddUISprite(scene, ConstructButtonSprite(1, (Vector2) {0.2, 0.2}, (Vector2) {0.55, 0.55}, "BACK", _InsToHome));
    AddUISprite(scene, ConstructImageSprite((Vector2){cx/2-3,cy*0.7},(Vector2){6,1.8},"Instruction/Ins_Title.bmp"));

}

Scene *ConstructInstructionScene() {
    Scene *obj = ConstructScene(_Instruction_Initialize);
    return obj;
}