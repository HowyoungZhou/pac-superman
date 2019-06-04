#include <sprite.h>
#include <extgraph.h>
#include <vector2.h>
#include <engine.h>
#include <graphics.h>
#include "imgui.h"
#include <drawing.h>
#include "hp.h"

#define ANGLE 30
#define PACMAN_SIZE 0.18
#define SPEED 1.0

static double cx,cy;

static void DrawPac(){

    TurnPolarAngleTo(ANGLE);
    MovePolarPen(PACMAN_SIZE / 2);
    DrawArc((PACMAN_SIZE) / 2, ANGLE, 360 - 2 * ANGLE);
    TurnPolarAngle(180 - 2 * ANGLE );
    DrawPolarLine(PACMAN_SIZE / 2);
    TurnPolarAngle( 2 * ANGLE - 180);
    DrawPolarLine(PACMAN_SIZE / 2);

}

static void _Render(Sprite *this){

    int i,n=3;

    MovePen(0.1,0.15);
    DrawTextString("HP");

    for(i=1;i<=n;i++){
        MovePen(0.25+0.3*i,0.225);
        DrawPac();
    }

}

static void _Destruct(Sprite *this) {
    free(this->property);
    DestructSprite(this);
}

Sprite *ConstructHPSprite(){
    cx = GetWindowWidth();
    cy = GetWindowHeight();

    Sprite *obj= ConstructSprite((Vector2){0.1,0.1},
                                 (Vector2){2,2},ZERO_VECTOR);


    obj->Destruct = _Destruct;
    obj->renderer.Render = _Render;
    return obj;
}