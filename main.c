#include <graphics.h>
#include <events.h>
#include <colors.h>
#include <engine.h>
#include <controller.h>
#include <game_controller.h>

#include "game_home_scene.h"

void Main() {
    InitGraphics();
    InitEvents();
    DefineColors();
    InitController();
    InitGameController();
    PushScene(ConstructHomeScene());
    InitEngine();
}
