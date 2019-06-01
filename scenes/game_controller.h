#ifndef PAC_SUPERMAN_GAME_STATE_H
#define PAC_SUPERMAN_GAME_STATE_H

typedef enum {
    EASY, NORMAL, HARD
} Difficulty;

void ResetGameState();

void ChangeScore(int change);

Difficulty GetDifficulty();

void SetDifficulty(Difficulty difficulty);

bool GetPowerMode();

void SetPowerMode(bool value);

#endif //PAC_SUPERMAN_GAME_STATE_H
