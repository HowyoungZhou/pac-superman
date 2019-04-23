#include <extgraph.h>
#include "engine.h"
#include "drawing.h"
#include "example_sprite.h"
#include "sprite.h"

void MainTimerHandler(int timerID) {
    _ClearScreen();
    //TODO: 碰撞检测、位置计算、调用渲染方法
}

void _ClearScreen() {
    SetEraseMode(TRUE);
    StartFilledRegion(1.);
    DrawRectangle(0, 0, GetWindowWidth(), GetWindowHeight());
    EndFilledRegion();
    SetEraseMode(FALSE);
}
