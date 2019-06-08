#include <sprite.h>
#include <scene.h>
#include <map_sprite.h>
#include <pellet_sprite.h>
#include <game_menu.h>
#include <graphics.h>
#include <pacman_sprite.h>
#include <power_pellet_sprite.h>
#include <ghost_blinky_sprite.h>
#include <autonav.h>
#include <autonav_route_sprite.h>
#include <example_controllable_sprite.h>
#include "game_scene.h"
#include <dynamic_array.h>
#include <button.h>
#include <hp.h>
#include <score.h>
#include <scene.h>
#include <engine.h>
#include <game_instruction_scene.h>
#include <game_RankingList_scene.h>
#include <about_scene.h>
#include <ghost_pinky_sprite.h>
#include <ghost_inky_sprite.h>
#include <ghost_clyde_sprite.h>
#include <ghost_sprite.h>
#include "game_controller.h"
#include <eagle_sprite.h>

#define WALKABLE_TILES_PAGE_SIZE 1000
#define PELLET_SIZE_RATIO 0.25
#define POWER_PELLET_SIZE_RATIO 0.7

#define DEFAULT_PAC_MAN_COLOR "PacManYellow"

static void _AddPellets(Sprite *sprite, unsigned int x, unsigned int y, short id);

static void _Initialize(Scene *scene);

static Scene *_currentScene = NULL;
static string _mapName = NULL;
static Heros _heros;
static DynamicArray _walkableTiles;

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
    NewGame();
}

void _GameToRank() {
    PushScene(ConstructRankingListScene());
}

void _GameToAbout() {
    PushScene(ConstructAboutScene());
}

static void _AddPellets(Sprite *sprite, unsigned int x, unsigned int y, short id) {
    switch (id) {
        case PELLET_TILE:;
            Vector2 size = GetTileSize(sprite);
            Vector2 position = VAdd(GetTilePosition(sprite, x, y), VMultiply((1. - PELLET_SIZE_RATIO) / 2., size));
            AddGameSprite(_currentScene, ConstructPellet(position, VMultiply(PELLET_SIZE_RATIO, size)));
            ChangeRemainingPellets(1);
            break;
        case POWER_PELLET_TILE:;
            Vector2 powerSize = GetTileSize(sprite);
            Vector2 powerPosition = VAdd(GetTilePosition(sprite, x, y),
                                         VMultiply((1. - POWER_PELLET_SIZE_RATIO) / 2., powerSize));
            AddGameSprite(_currentScene,
                          ConstructPowerPellet(powerPosition, VMultiply(POWER_PELLET_SIZE_RATIO, powerSize)));
            ChangeRemainingPellets(1);
            break;
        default:
            break;
    }
}

static inline Vector2 *_ConstructPosPtr(Vector2 pos) {
    Vector2 *posPtr = malloc(sizeof(Vector2));
    *posPtr = pos;
    return posPtr;
}

static void _FindAllWalkable(Sprite *sprite, unsigned int x, unsigned int y, short id) {
    if (IsTileWalkable(sprite, x, y)) ArrayAddElement(&_walkableTiles, _ConstructPosPtr(GetTilePosition(sprite, x, y)));
}

static void _Initialize(Scene *scene) {
    _currentScene = scene;

    double cx, cy;
    cx = GetWindowWidth();
    cy = GetWindowHeight();

    // 重置游戏数据
    ResetGameState();

    // 游戏菜单
    Sprite *menu = ConstructGameMenuSprite();

    //添加右上角的按钮
    AddUISprite(scene,
                ConstructButtonSprite(1, (Vector2) {cx - 4 + 0.1, cy - 0.9}, (Vector2) {0.8, 0.4}, "Pause",
                                      PauseCallback));
    AddUISprite(scene,
                ConstructButtonSprite(2, (Vector2) {cx - 4 + 1.1, cy - 0.9}, (Vector2) {0.8, 0.4}, "Reset",
                                      ResetCallback));
    AddUISprite(scene, ConstructButtonSprite(3, (Vector2) {cx - 4 + 2.1, cy - 0.9}, (Vector2) {0.8, 0.4}, "Rank",
                                             _GameToRank));
    AddUISprite(scene,
                ConstructButtonSprite(4, (Vector2) {cx - 4 + 3.1, cy - 0.9}, (Vector2) {0.8, 0.4}, "About",
                                      _GameToAbout));

    //添加左上角的分数
    AddUISprite(scene, ConstructScoreSprite());

    //添加左下角生命值
    AddUISprite(scene, ConstructHPSprite());

    // 游戏地图
    _heros.map = ConstructMapSprite(_mapName, "colliders_dict.tcd", (Vector2) {0, 0.4},
                                    (Vector2) {cx, cy - menu->size.y - 0.4 - 0.72});
    AddGameSprite(scene, _heros.map);

    // 添加吃豆人
    GameObject pacman;
    FindGameObjectOfMap(_heros.map, "PacMan", &pacman);
    _heros.pacman = ConstructPacmanSprite(pacman.position, pacman.size, DEFAULT_PAC_MAN_COLOR);
    AddGameSprite(_currentScene, _heros.pacman);

    // 添加豆子
    ForEachTile(_heros.map, _AddPellets);

    // 缓存所有的可到达位置
    if (_walkableTiles.length) FreeDynamicArray(&_walkableTiles, free);
    InitDynamicArray(&_walkableTiles, WALKABLE_TILES_PAGE_SIZE);
    ForEachTile(_heros.map, _FindAllWalkable);

    // 添加鬼
    GameObject blinky, pinky, inky, clyde;
    FindGameObjectOfMap(_heros.map, "Blinky", &blinky);
    FindGameObjectOfMap(_heros.map, "Pinky", &pinky);
    FindGameObjectOfMap(_heros.map, "Inky", &inky);
    FindGameObjectOfMap(_heros.map, "Clyde", &clyde);
    _heros.blinky = ConstructGhostBlinkySprite(blinky.position, blinky.size);
    _heros.pinky = ConstructGhostPinkySprite(pinky.position, pinky.size);
    _heros.inky = ConstructGhostInkySprite(inky.position, inky.size);
    _heros.clyde = ConstructGhostClydeSprite(clyde.position, clyde.size);
    AddGameSprite(_currentScene, _heros.blinky);
    AddGameSprite(_currentScene, _heros.pinky);
    AddGameSprite(_currentScene, _heros.inky);
    AddGameSprite(_currentScene, _heros.clyde);

    // 设置寻径步长值
    double step = GetTileSize(_heros.map).x / 2;
    ChangePathfindingStep(step);
    ChangeMaxNodeCounts((_heros.map->size.x / step) * (_heros.map->size.y / step));
    ChangePathfindingBorder(_heros.map->position, _heros.map->size);
    AddUISprite(scene, menu);
}

DynamicArray GetAllWalkableTiles() {
    return _walkableTiles;
}

void RevivePacMan() {
    Scene *current = GetCurrentScene();

    Sprite *pacmanSprite = _heros.pacman;
    GameObject pacman;
    FindGameObjectOfMap(_heros.map, "PacMan", &pacman);
    pacmanSprite->position = pacman.position;

    ResetBlinky(_heros.blinky);
    ResetClyde(_heros.clyde);
    ResetInky(_heros.inky);
    ResetPinky(_heros.pinky);
}

static void _Destruct(Scene *this) {
    DestructScene(this);
    if (_walkableTiles.length)FreeDynamicArray(&_walkableTiles, free);
}

Scene *ConstructGameScene(string mapName) {
    _mapName = mapName;
    Scene *obj = ConstructScene(_Initialize);
    return obj;
}

void NewGame() {
    ReplaceScene(ConstructGameScene(_mapName));
}

void PowerModeOn() {
    Sprite *ghosts[] = {_heros.clyde, _heros.inky, _heros.pinky, _heros.blinky};
    for (int i = 0; i < sizeof(ghosts) / sizeof(Sprite *); i++) {
        Sprite *ghostSprite = ghosts[i];
        if (!ghostSprite) continue;
        Ghost *ghost = ghostSprite->property;
        if (ghost->state == CHASING) ghost->state = CHASED_AFTER;
        ghost->chasedCountDown = GetGameObjectOption().ghostChasedCountDown;
    }
}

Heros GetCurrentHeros() {
    return _heros;
}
