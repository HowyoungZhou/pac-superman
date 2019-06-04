#include <scene.h>
#include <button.h>
#include <vector2.h>
#include <engine.h>
#include <image.h>
#include <graphics.h>
#include <extgraph.h>
#include <game_home_scene.h>
#include "about_scene.h"

static double cx,cy;

void _AboutToHome(){
    ReplaceScene(ConstructHomeScene());
}

void _About_Initialize(Scene *scene) {

    cx = GetWindowWidth();
    cy = GetWindowHeight();

    AddUISprite(scene, ConstructButtonSprite(1, (Vector2) {0.2, 0.2}, (Vector2) {0.55, 0.55}, "BACK", _AboutToHome));
    AddUISprite(scene, ConstructImageSprite((Vector2){cx/2-5,cy/2-2.5},(Vector2){10,6},"about/about.bmp"));

}

Scene *ConstructAboutScene() {
    Scene *obj = ConstructScene(_About_Initialize);
    return obj;
}