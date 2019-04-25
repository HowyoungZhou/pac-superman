#ifndef PAC_SUPERMAN_ENGINE_H
#define PAC_SUPERMAN_ENGINE_H

#include "sprite.h"

#define MAIN_TIMER_INTERVAL 20

#define MAIN_TIMER_ID 0

void MainTimerHandler(int timerID);

void _ClearScreen();

void _UpdatePosition(Sprite *sprite);

void _RenderSprite(Sprite *sprite);

#endif //PAC_SUPERMAN_ENGINE_H
