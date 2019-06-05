#ifndef PAC_SUPERMAN_GAME_STATE_H
#define PAC_SUPERMAN_GAME_STATE_H

typedef enum {
    EASY = 0, NORMAL, HARD
} Difficulty;

typedef struct {
    double playerSpeed;
    double ghostChasingSpeed;
    double ghostChasedSpeed;
} GameObjectOption;

void ResetGameState();

void ChangeScore(int change);

Difficulty GetDifficulty();

void SetDifficulty(Difficulty difficulty);

GameObjectOption GetGameObjectOption();

void PowerModeOn();

#endif //PAC_SUPERMAN_GAME_STATE_H
