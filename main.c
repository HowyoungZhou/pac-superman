#include <graphics.h>
#include <events.h>
#include <colors.h>
#include <engine.h>
#include <controller.h>

#include "test_scene.h"

void Main() {
    InitConsole();
    InitGraphics();
    InitEvents();
    DefineColors();
    InitController();
    PushScene(ConstructTestScene());
    InitEngine();
}
