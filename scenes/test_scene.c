#include <scene.h>
#include <example_controllable_sprite.h>
#include <pellet.h>
#include <pacman_sprite.h>
#include <button.h>
#include <game_menu.h>
#include <vector2.h>
#include <engine.h>
#include "test_scene.h"

void PauseCallback(Sprite *button) {
    if (IsPaused()) {
        ResumeGame();
        ((Button *) button->property)->label = "Pause";
    } else {
        PauseGame();
        ((Button *) button->property)->label = "Resume";
    }
}

void _Initialize(Scene *scene) {
    AddGameSprite(scene, ConstructExampleControllableSprite());
    AddGameSprite(scene, ConstructPellet((Vector2) {1, 1}, (Vector2) {0.1, 0.1}));
    AddGameSprite(scene, ConstructPacmanSprite());
    AddUISprite(scene, ConstructButtonSprite(1, (Vector2) {1, 2}, (Vector2) {1, 0.6}, "Pause", PauseCallback));
    AddUISprite(scene, ConstructGameMenuSprite());
}

Scene *ConstructTestScene() {
    Scene *obj = ConstructScene(_Initialize);
    return obj;
}