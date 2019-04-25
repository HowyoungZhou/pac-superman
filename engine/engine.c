#include <extgraph.h>
#include "engine.h"
#include "sprite.h"
#include "sprites_list.h"
#include "drawing.h"

void MainTimerHandler(int timerID) {
    _ClearScreen();
    //TODO: 碰撞检测
    ForEachSprite(_UpdatePosition);
    ForEachSprite(_RenderSprite);
}

void _UpdatePosition(Sprite *sprite) {
    sprite->position = Vector2Add(sprite->position, Vector2Multiply(MAIN_TIMER_INTERVAL, sprite->velocity));
}

void _RenderSprite(Sprite *sprite) {
    //TODO: 目前直接调用 Render() 方法，需添加动画系统
    sprite->renderer.Render(sprite);
}

void _ClearScreen() {
    SetEraseMode(TRUE);
    StartFilledRegion(1.);
    DrawRectangle(0, 0, GetWindowWidth(), GetWindowHeight());
    EndFilledRegion();
    SetEraseMode(FALSE);
}
