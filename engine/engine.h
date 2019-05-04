#ifndef PAC_SUPERMAN_ENGINE_H
#define PAC_SUPERMAN_ENGINE_H

#include "sprite.h"

#define RENDERER_TIMER_ID 0
#define PHYSICAL_ENGINE_TIMER_ID 1
#define RENDERER_TIMER_INTERVAL 5
#define PHYSICAL_ENGINE_TIMER_INTERVAL 1

void InitEngine();

void RegisterSprite(Sprite *sprite);

void RegisterUISprite(Sprite *uiSprite);

void PauseGame();

void ResumeGame();

#endif //PAC_SUPERMAN_ENGINE_H
