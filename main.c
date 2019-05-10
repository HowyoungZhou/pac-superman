#include "graphics.h"
#include "engine.h"
#include "sprite.h"
#include "example_sprite.h"
#include <example_controllable_sprite.h>
#include <pellet.h>
#include <controller.h>
#include <colors.h>
#include <button.h>
#include <events.h>
#include <game_menu.h>

void PauseCallback(Sprite *button) {
    if (IsPaused()) {
        ResumeGame();
        ((Button *) button->property)->label = "Pause";
    } else {
        PauseGame();
        ((Button *) button->property)->label = "Resume";
    }
}

// 仅做测试，随后删除
void RegisterSprites() {
    RegisterSprite(ConstructExampleControllableSprite());
    RegisterSprite(ConstructPellet((Vector2) {1, 1}, (Vector2) {0.1, 0.1}));
    RegisterUISprite(ConstructButtonSprite(1, (Vector2) {1, 2}, (Vector2) {1, 0.6}, "Pause", PauseCallback));
    RegisterUISprite(ConstructGameMenuSprite());
}

void Main() {
    InitConsole();
    InitGraphics();
    InitEvents();
    DefineColors();
    RegisterSprites();
    InitController();
    InitEngine();
}
