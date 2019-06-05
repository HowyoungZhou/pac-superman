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

static const string _ghosts[] = {"GhostBlinky"};
static Difficulty _difficulty;
static GameState _state = (GameState) {.life = 3, .score = 0};

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

void PowerModeOn() {
    for (int i = 0; i < sizeof(_ghosts) / sizeof(string); i++) {
        Sprite *ghost = FindGameSpriteByName(GetCurrentScene(), _ghosts[i]);
        if (!ghost) continue;
        ((Ghost *) ghost->property)->state = CHASED_AFTER;
    }
}