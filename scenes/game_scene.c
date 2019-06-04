#include <sprite.h>
#include <scene.h>
#include <map_sprite.h>
#include <pellet_sprite.h>
#include <game_menu.h>
#include <graphics.h>
#include <pacman_sprite.h>
#include <power_pellet_sprite.h>
#include <example_bitmap_sprite.h>
#include <autonav.h>
#include <autonav_route_sprite.h>
#include <example_controllable_sprite.h>
#include "game_scene.h"
#include <button.h>
#include <hp.h>
#include <score.h>
#include <scene.h>
#include <engine.h>
#include <game_instruction_scene.h>
#include <game_RankingList_scene.h>
#include <about_scene.h>

#define PELLET_SIZE_RATIO 0.25
#define POWER_PELLET_SIZE_RATIO 0.7

#define PELLET_TILE 54
#define POWER_PELLET_TILE 42

static double cx,cy;

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

void PauseCallback(Sprite *button) {
    if (IsPaused()) {
        ResumeGame();
        ((Button *) button->property)->label = "Pause";
    } else {
        PauseGame();
        ((Button *) button->property)->label = "Resume";
    }
}

void ResetCallback(Sprite *button) {
    ReplaceScene(ConstructGameScene());
}

void _GameToRank(){
    ReplaceScene(ConstructRankingListScene());
}

void _GameToAbout(){
    ReplaceScene(ConstructAboutScene());
}

void _Initialize(Scene *scene) {
    _currentScene = scene;
    cx = GetWindowWidth();
    cy = GetWindowHeight();

    // 游戏菜单
    Sprite *menu = ConstructGameMenuSprite();
    AddUISprite(scene, menu);

    //添加左上角的按钮
    AddUISprite(scene, ConstructButtonSprite(1, (Vector2) {0.1, cy-0.9}, (Vector2) {0.8, 0.4}, "Pause", PauseCallback));
    AddUISprite(scene, ConstructButtonSprite(2, (Vector2) {1.1, cy-0.9}, (Vector2) {0.8, 0.4}, "Reset", ResetCallback));
    AddUISprite(scene, ConstructButtonSprite(3, (Vector2) {2.1, cy-0.9}, (Vector2) {0.8, 0.4}, "Rank", _GameToRank));
    AddUISprite(scene, ConstructButtonSprite(4, (Vector2) {3.1, cy-0.9}, (Vector2) {0.8, 0.4}, "About", _GameToAbout));

    //添加右上角的分数
    AddUISprite(scene,ConstructScoreSprite());

    //添加左下角生命值
    AddUISprite(scene,ConstructHPSprite());

    // 游戏地图
    Sprite *map = ConstructMapSprite("maps/classic", "colliders_dict.tcd", ZERO_VECTOR,
                                     (Vector2) {GetWindowWidth(), GetWindowHeight() - menu->size.y});
    AddGameSprite(scene, map);

    // 添加吃豆人
    GameObject pacman;
    FindGameObjectOfMap(map, "PacMan", &pacman);
    Sprite *pacmanSprite = ConstructPacmanSprite(pacman.position, pacman.size);
    AddGameSprite(scene, pacmanSprite);

    // 添加豆子
    ForEachTile(map, _ForEachTile);

    // 添加测试鬼
    Sprite *ghost = ConstructExampleBitmapSprite(pacmanSprite);
    AddGameSprite(scene, ghost);
    ChangePathfindingStep(GetTileSize(map).x/2);
    //AddUISprite(scene, ConstructAutoNavRouteSprite(ghost));

}

Scene *ConstructGameScene() {
    Scene *obj = ConstructScene(_Initialize);
    return obj;
}