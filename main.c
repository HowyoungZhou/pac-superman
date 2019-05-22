#include <graphics.h>
#include <events.h>
#include <colors.h>
#include <engine.h>
#include <controller.h>

#include "game_home_scene.h"

void Main() {
    InitConsole();
    InitGraphics();
    InitEvents();
    DefineColors();
    InitController();
    PushScene(ConstructHomeScene());
    InitEngine();
}
