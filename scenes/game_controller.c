#include <stdbool.h>
#include <genlib.h>
#include <sprite.h>
#include <scene.h>
#include <engine.h>
#include <assets.h>
#include <ghost_sprite.h>
#include "game_controller.h"

typedef struct {
    int score;
    unsigned int life;
} GameState;

static const string _ghosts[] = {"GhostBlinky", "GhostPinky", "GhostInky", "GhostClyde"};
static Difficulty _difficulty;
static GameState _state = (GameState) {.life = 3, .score = 0};
static GameObjectOption _option;
static const GameObjectOption _options[] = {
        (GameObjectOption) {
                .playerSpeed = 1.,
                .ghostChasingSpeed = 0.5,
                .ghostChasedSpeed = 0.4
        },
        (GameObjectOption) {
                .playerSpeed = 1.,
                .ghostChasingSpeed = 0.7,
                .ghostChasedSpeed = 0.6
        },
        (GameObjectOption) {
                .playerSpeed = 1.,
                .ghostChasingSpeed = 1.,
                .ghostChasedSpeed = 0.8
        }
};

void ResetGameState() {
    _state = (GameState) {.life = 3, .score = 0};
}

void ChangeScore(int change) {
    _state.score += change;
}

Difficulty GetDifficulty() {
    return _difficulty;
}

void SetDifficulty(Difficulty difficulty) {
    _difficulty = difficulty;
}

GameObjectOption GetGameObjectOption() {
    return _options[_difficulty];
}

void PowerModeOn() {
    for (int i = 0; i < sizeof(_ghosts) / sizeof(string); i++) {
        Sprite *ghostSprite = FindGameSpriteByName(GetCurrentScene(), _ghosts[i]);
        if (!ghostSprite) continue;
        Ghost *ghost = ghostSprite->property;
        if (ghost->state == CHASING) ghost->state = CHASED_AFTER;
    }
}