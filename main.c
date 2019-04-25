#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include "engine.h"
#include "sprite.h"
#include "example_sprite.h"
#include "sprites_list.h"

// 仅做测试，随后删除
void RegisterSprites() {
    Sprite *exampleSprite1 = ConstructExampleSprite();
    Sprite *exampleSprite2 = ConstructExampleSprite();
    Sprite *exampleSprite3 = ConstructExampleSprite();

    exampleSprite2->velocity = (Vector2) {0, 0.001};
    exampleSprite3->velocity = (Vector2) {0.001, 0.001};

    RegisterSprite(exampleSprite1);
    RegisterSprite(exampleSprite2);
    RegisterSprite(exampleSprite3);
}

void Main() {
    InitGraphics();
    RegisterSprites();
    registerTimerEvent(MainTimerHandler);
    startTimer(MAIN_TIMER_ID, MAIN_TIMER_INTERVAL);
}
