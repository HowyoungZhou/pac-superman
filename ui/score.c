#include <sprite.h>
#include <extgraph.h>
#include <vector2.h>
#include <engine.h>
#include <graphics.h>
#include "game_menu.h"
#include "menu.h"
#include "imgui.h"
#include "score.h"

#define NUMBER "  0 0 0 0 0 0 "
static double cx,cy;

static void _Render(Sprite *this){
    MovePen(cx-1.75,cy-0.75);
    DrawTextString("SCORE");
    DrawTextString(NUMBER);
}

static void _Destruct(Sprite *this) {
    free(this->property);
    DestructSprite(this);
}


Sprite *ConstructScoreSprite(){
    cx = GetWindowWidth();
    cy = GetWindowHeight();

    Sprite *obj= ConstructSprite((Vector2){cx-2,cy-1},
                                 (Vector2){2,2},ZERO_VECTOR);


    obj->Destruct = _Destruct;
    obj->renderer.Render = _Render;
    return obj;
}