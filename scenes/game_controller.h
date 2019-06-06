#ifndef PAC_SUPERMAN_GAME_STATE_H
#define PAC_SUPERMAN_GAME_STATE_H

typedef enum {
    EASY = 0, NORMAL, HARD
} Difficulty;

typedef struct {
    double playerSpeed;
    double ghostChasingSpeed;
    double ghostChasedSpeed;
    double ghostChasedCountDown;
} GameObjectOption;

void ResetGameState();

void ChangeLife(int change);

unsigned int GetLife();

void ChangeScore(int change);

int GetScore();

Difficulty GetDifficulty();

void SetDifficulty(Difficulty difficulty);

GameObjectOption GetGameObjectOption();

#endif //PAC_SUPERMAN_GAME_STATE_H
