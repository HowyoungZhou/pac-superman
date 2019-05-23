#include <scene.h>
#include <example_controllable_sprite.h>
#include <pellet_sprite.h>
#include <pacman_sprite.h>
#include <button.h>
#include <game_menu.h>
#include <vector2.h>
#include <engine.h>
#include <example_bitmap_sprite.h>
#include <graphics.h>
#include <walls.h>
#include <map_sprite.h>
#include "game_scene.h"

void _Initialize(Scene *scene) {
    Sprite *menu = ConstructGameMenuSprite();
    AddUISprite(scene, menu);

//    double height = GetWindowHeight() - menu->size.y;
//    double width = GetWindowWidth();
//    AddGameSprite(scene, ConstructWallsSprite((width - height) / 2., height));

    AddGameSprite(scene, ConstructMapSprite("maps/classic", "colliders_dict.tcd", ZERO_VECTOR,
                                            (Vector2) {GetWindowWidth(), GetWindowHeight() - menu->size.y}));
    AddGameSprite(scene, ConstructPellet((Vector2) {1, 1}, (Vector2) {0.1, 0.1}));
    AddGameSprite(scene, ConstructExampleBitmapSprite());
    AddGameSprite(scene, ConstructPacmanSprite());
}

Scene *ConstructGameScene() {
    Scene *obj = ConstructScene(_Initialize);
    return obj;
}