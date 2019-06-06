#include <imgui.h>
#include <graphics.h>
#include <extgraph.h>
#include <sprite.h>
#include <engine.h>
#include <game_scene.h>
#include "textbox.h"

static int   _GAMESTART = 0;
static char memo[80]="NAME";
static double cx,cy;

void _Render()
{
    double fH = GetFontHeight();
    cx = GetWindowWidth();
    cy = GetWindowHeight();

    //绘制对话框
    drawRectangle(cx/2-2, cy/2-1,4, 2.5, 1);
    SetPenColor("Brown");
    drawLabel(cx/2-TextStringWidth("ENTER YOUR NAME!")/2, cy/2+1, "ENTER YOUR NAME!");
    textbox(GenUIID(0), cx/2-1.5, cy/2, 3, fH*2.5, memo, sizeof(memo));

    if (button(GenUIID(0), cx/2+1, cy/2-0.8, 0.5, 0.4,"OK"))
        _GAMESTART = !_GAMESTART;
    if( _GAMESTART) {
        //ReplaceScene(ConstructGameScene());
        _GAMESTART = !_GAMESTART;
    }

}

static void _Destruct(Sprite *this) {
    free(this->property);
    DestructSprite(this);
}

Sprite *ConstructTextBoxSprite(){
    cx = GetWindowWidth();
    cy = GetWindowHeight();

    Sprite *obj= ConstructSprite((Vector2){cx-2,cy-1},
                                 (Vector2){2,2},ZERO_VECTOR);

    obj->Destruct = _Destruct;
    obj->renderer.Render = _Render;
    return obj;
}