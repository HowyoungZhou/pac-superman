#include <stdbool.h>
#include "game_controller.h"

typedef struct {
    int score;
    unsigned int life;
    bool powerMode;
} GameState;

static Difficulty _difficulty;
static GameState _state = (GameState) {.life = 3, .score = 0, .powerMode = false};

void ResetGameState() {
    _state = (GameState) {.life = 3, .score = 0, .powerMode = false};
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

bool GetPowerMode() {
    return _state.powerMode;
}

void SetPowerMode(bool value) {
    _state.powerMode = value;
}
