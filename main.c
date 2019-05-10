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
#include <menu.h>
#include <imgui.h>
#include <extgraph.h>

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
}

void OnMenuItemSelected(struct MenuList *sender, int selectedIndex) {
    if (selectedIndex == 2)ExitGraphics();
}

void TestMenu() {
    Sprite *menu = ConstructMenuSprite(ConstructMenu(2,
                                                     ConstructMenuList(2, OnMenuItemSelected, 3, "Game",
                                                                       "Pause/Resume", "Exit"),
                                                     ConstructMenuList(3, NULL, 3, "Help", "How to play?",
                                                                       "About")));
    RegisterUISprite(menu);
}

void Main() {
    InitConsole();
    InitGraphics();
    InitEvents();
    DefineColors();
    RegisterSprites();
    TestMenu();
    InitController();
    InitEngine();
}
