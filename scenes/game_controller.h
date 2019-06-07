#ifndef PAC_SUPERMAN_GAME_STATE_H
#define PAC_SUPERMAN_GAME_STATE_H

#define MAX_NAME_LENGTH 100
#define RANK_FILE "rank.dat"
#define MAX_RANK_LENGTH 5

typedef enum {
    EASY = 0, NORMAL, HARD
} Difficulty;

typedef struct {
    double playerSpeed;
    double ghostChasingSpeed;
    double ghostChasedSpeed;
    double ghostChasedCountDown;
} GameObjectOption;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int score;
} RankListItem;

typedef LinkedList RankList;
typedef LinkedListNode RankListNode;

void ResetGameState();

void ChangeLife(int change);

unsigned int GetLife();

void ChangeScore(int change);

int GetScore();

void ChangeRemainingPellets(int change);

unsigned int GetRemainingPellets();

Difficulty GetDifficulty();

void SetDifficulty(Difficulty difficulty);

GameObjectOption GetGameObjectOption();

void InitGameController();

RankList GetRank();

bool AddToRank(string name, int score);

#endif //PAC_SUPERMAN_GAME_STATE_H
