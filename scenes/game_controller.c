#include <sprite.h>
#include <scene.h>
#include <engine.h>
#include <assets.h>
#include "game_controller.h"

typedef struct {
    int score;
    unsigned int life;
} GameState;

static Difficulty _difficulty;
static GameState _state = (GameState) {.life = 3, .score = 0};
static const GameObjectOption _options[] = {
        (GameObjectOption) {
                .playerSpeed = 1.,
                .ghostChasingSpeed = 0.5,
                .ghostChasedSpeed = 0.4,
                .ghostChasedCountDown = 10000
        },
        (GameObjectOption) {
                .playerSpeed = 1.,
                .ghostChasingSpeed = 0.7,
                .ghostChasedSpeed = 0.6,
                .ghostChasedCountDown = 10000
        },
        (GameObjectOption) {
                .playerSpeed = 1.,
                .ghostChasingSpeed = 1.,
                .ghostChasedSpeed = 0.8,
                .ghostChasedCountDown = 10000
        }
};

void ResetGameState() {
    _state = (GameState) {.life = 3, .score = 0};
}

void ChangeLife(int change) {
    _state.life += change;
}

unsigned int GetLife() {
    return _state.life;
}

void ChangeScore(int change) {
    _state.score += change;
}

int GetScore() {
    return _state.score;
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
