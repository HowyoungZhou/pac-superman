#include "graphics.h"
#include "engine.h"
#include "sprite.h"
#include "example_sprite.h"
#include "sprites_list.h"
#include <example_animated_sprite.h>
#include <example_controllable_sprite.h>
#include <controller.h>

// 仅做测试，随后删除
void RegisterSprites() {
    Sprite *exampleSprite1 = ConstructExampleAnimatedSprite();
    Sprite *exampleSprite2 = ConstructExampleSprite();
    Sprite *exampleSprite3 = ConstructExampleSprite();
    Sprite *exampleSprite4 = ConstructExampleControllableSprite();

    exampleSprite2->velocity = (Vector2) {0, 0.001};
    exampleSprite3->velocity = (Vector2) {0.001, 0.001};

    RegisterSprite(exampleSprite1);
    RegisterSprite(exampleSprite2);
    RegisterSprite(exampleSprite3);
    RegisterSprite(exampleSprite4);
}

void Main() {
    InitConsole();
    InitGraphics();
    RegisterSprites();
    InitController();
    InitEngine();
    registerTimerEvent(MainTimerHandler);
    startTimer(MAIN_TIMER_ID, MAIN_TIMER_INTERVAL);
}
