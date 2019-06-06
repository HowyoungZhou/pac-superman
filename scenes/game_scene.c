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
#include "game_controller.h"
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

#define PELLET_SIZE_RATIO 0.25
#define POWER_PELLET_SIZE_RATIO 0.7

#define PELLET_TILE 54
#define POWER_PELLET_TILE 42

static void _ForEachTile(Sprite *sprite, unsigned int x, unsigned int y, short id);

static void _Initialize(Scene *scene);

static Scene *_currentScene = NULL;
static Sprite *_currentMap = NULL;
static const string _ghosts[] = {"GhostBlinky", "GhostPinky", "GhostInky", "GhostClyde"};

static void _ForEachTile(Sprite *sprite, unsigned int x, unsigned int y, short id) {
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

void _GameToRank() {
    ReplaceScene(ConstructRankingListScene());
}

void _GameToAbout() {
    ReplaceScene(ConstructAboutScene());
}

static inline void _AddGhost() {
    GameObject blinky, pinky, inky, clyde;
    FindGameObjectOfMap(_currentMap, "Blinky", &blinky);
    FindGameObjectOfMap(_currentMap, "Pinky", &pinky);
    FindGameObjectOfMap(_currentMap, "Inky", &inky);
    FindGameObjectOfMap(_currentMap, "Clyde", &clyde);
    AddGameSprite(_currentScene, ConstructGhostBlinkySprite(blinky.position, blinky.size));
    AddGameSprite(_currentScene, ConstructGhostPinkySprite(pinky.position, pinky.size));
    AddGameSprite(_currentScene, ConstructGhostInkySprite(inky.position, inky.size));
    AddGameSprite(_currentScene, ConstructGhostClydeSprite(clyde.position, clyde.size));
}

static inline void _AddPacMan() {
    GameObject pacman;
    FindGameObjectOfMap(_currentMap, "PacMan", &pacman);
    Sprite *pacmanSprite = ConstructPacmanSprite(pacman.position, pacman.size);
    AddGameSprite(_currentScene, pacmanSprite);
}

static inline void _AddPellet() {
    ForEachTile(_currentMap, _ForEachTile);
}

static void _Initialize(Scene *scene) {
    _currentScene = scene;

    double cx, cy;
    cx = GetWindowWidth();
    cy = GetWindowHeight();

    // 游戏菜单
    Sprite *menu = ConstructGameMenuSprite();

    //添加左上角的按钮
    AddUISprite(scene,
                ConstructButtonSprite(1, (Vector2) {0.1, cy - 0.9}, (Vector2) {0.8, 0.4}, "Pause", PauseCallback));
    AddUISprite(scene,
                ConstructButtonSprite(2, (Vector2) {1.1, cy - 0.9}, (Vector2) {0.8, 0.4}, "Reset", ResetCallback));
    AddUISprite(scene, ConstructButtonSprite(3, (Vector2) {2.1, cy - 0.9}, (Vector2) {0.8, 0.4}, "Rank", _GameToRank));
    AddUISprite(scene,
                ConstructButtonSprite(4, (Vector2) {3.1, cy - 0.9}, (Vector2) {0.8, 0.4}, "About", _GameToAbout));

    //添加右上角的分数
    AddUISprite(scene, ConstructScoreSprite());

    //添加左下角生命值
    AddUISprite(scene, ConstructHPSprite());

    // 游戏地图
    _currentMap = ConstructMapSprite("maps/classic", "colliders_dict.tcd", (Vector2) {0, 0.4},
                                     (Vector2) {GetWindowWidth(), GetWindowHeight() - menu->size.y - 0.4 - 0.72});
    AddGameSprite(scene, _currentMap);

    _AddPacMan();
    _AddPellet();
    _AddGhost();

    // 设置寻径步长值
    ChangePathfindingStep(GetTileSize(_currentMap).x / 2);
    AddUISprite(scene, menu);
}

void RevivePacMan() {
    Scene *current = GetCurrentScene();
    RemoveGameSprite(current, "PacMan");
    for (int i = 0; i < sizeof(_ghosts) / sizeof(string); i++) {
        RemoveGameSprite(current, _ghosts[i]);
    }
    _AddPacMan();
    _AddGhost();
}

Scene *ConstructGameScene() {
    Scene *obj = ConstructScene(_Initialize);
    return obj;
}

void PowerModeOn() {
    for (int i = 0; i < sizeof(_ghosts) / sizeof(string); i++) {
        Sprite *ghostSprite = FindGameSpriteByName(GetCurrentScene(), _ghosts[i]);
        if (!ghostSprite) continue;
        Ghost *ghost = ghostSprite->property;
        if (ghost->state == CHASING) ghost->state = CHASED_AFTER;
        ghost->chasedCountDown = GetGameObjectOption().ghostChasedCountDown;
    }
}