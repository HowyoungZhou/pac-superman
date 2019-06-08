#include <sprite.h>
#include <extgraph.h>
#include <vector2.h>
#include <engine.h>
#include <graphics.h>
#include <game_controller.h>
#include "game_menu.h"
#include "menu.h"
#include "imgui.h"
#include "score.h"

static double cx, cy;

static void _Render(Sprite *this) {
    char score[MAX_SCORE_LENGTH + 1];
    sprintf(score, "%0*d", MAX_SCORE_LENGTH, GetScore());
    MovePen(0.3, cy - 0.75);
    int size = GetPointSize();
    SetPointSize(18);
    DrawTextString("SCORE  ");
    DrawTextString(score);
    SetPointSize(size);
}

static void _Destruct(Sprite *this) {
    free(this->property);
    DestructSprite(this);
}


Sprite *ConstructScoreSprite() {
    cx = GetWindowWidth();
    cy = GetWindowHeight();

    Sprite *obj = ConstructSprite((Vector2) {0, cy - 1},
                                  (Vector2) {2, 1}, ZERO_VECTOR);


    obj->Destruct = _Destruct;
    obj->renderer.Render = _Render;
    return obj;
}