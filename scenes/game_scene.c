#include <sprite.h>
#include <scene.h>
#include <map_sprite.h>
#include <pellet_sprite.h>
#include <game_menu.h>
#include <graphics.h>
#include <pacman_sprite.h>
#include <power_pellet_sprite.h>
#include "game_scene.h"

#define PELLET_SIZE_RATIO 0.25
#define POWER_PELLET_SIZE_RATIO 0.7

#define PELLET_TILE 54
#define POWER_PELLET_TILE 42

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
        case POWER_PELLET_TILE:;
            Vector2 powerSize = GetTileSize(sprite);
            Vector2 powerPosition = VAdd(GetTilePosition(sprite, x, y),
                                         VMultiply((1. - POWER_PELLET_SIZE_RATIO) / 2., powerSize));
            AddGameSprite(_currentScene,
                          ConstructPowerPellet(powerPosition, VMultiply(POWER_PELLET_SIZE_RATIO, powerSize)));
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