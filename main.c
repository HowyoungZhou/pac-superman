#include "graphics.h"
#include "engine.h"
#include "sprite.h"
#include "example_sprite.h"
#include <example_controllable_sprite.h>
#include <pellet.h>
#include <controller.h>
#include <colors.h>
#include <button.h>

void PauseCallback(Sprite *button) {
    PauseGame();
}

// 仅做测试，随后删除
void RegisterSprites() {
    RegisterSprite(ConstructExampleControllableSprite());
    RegisterSprite(ConstructPellet((Vector2) {1, 1}, (Vector2) {0.1, 0.1}));
    RegisterSprite(ConstructButtonSprite(0, (Vector2) {1, 2}, (Vector2) {1, 0.6}, "", PauseCallback));
}

void Main() {
    InitConsole();
    InitGraphics();
    DefineColors();
    RegisterSprites();
    InitController();
    InitEngine();
}
