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
#include <assets.h>
#include "game_scene.h"

#define PELLET_SIZE_RATIO 0.25

#define PELLET_TILE 54

void _ForEachTile(Sprite *sprite, unsigned int x, unsigned int y, short id);

void _Initialize(Scene *scene);

static Scene *_currentScene = NULL;

void _ForEachTile(Sprite *sprite, unsigned int x, unsigned int y, short id) {
    switch (id) {
        case PELLET_TILE:;
            Vector2 size = GetTileSize(sprite);
            Vector2 position = VAdd(GetTilePosition(sprite, x, y), VMultiply((1. - PELLET_SIZE_RATIO) / 2., size));
            AddGameSprite(_currentScene, ConstructPellet(position, VMultiply(PELLET_SIZE_RATIO, size)));
            break;
        default:
            break;
    }
}

void _Initialize(Scene *scene) {
    _currentScene = scene;
    // 游戏菜单
    Sprite *menu = ConstructGameMenuSprite();
    AddUISprite(scene, menu);
    // 游戏地图
    Sprite *map = ConstructMapSprite("maps/classic", "colliders_dict.tcd", ZERO_VECTOR,
                                     (Vector2) {GetWindowWidth(), GetWindowHeight() - menu->size.y});
    AddGameSprite(scene, map);
    // 添加吃豆人
    GameObject pacman;
    FindGameObjectOfMap(map, "PacMan", &pacman);
    AddGameSprite(scene, ConstructPacmanSprite(pacman.position, pacman.size));
    // 添加豆子
    ForEachTile(map, _ForEachTile);
}

Scene *ConstructGameScene() {
    Scene *obj = ConstructScene(_Initialize);
    return obj;
}