#include <sprite.h>
#include <scene.h>
#include <engine.h>
#include <assets.h>
#include <extgraph.h>
#include "game_controller.h"
#include <end_game_box.h>

static inline bool _WriteRankList();

static inline bool _ReadRankList();

static inline RankListItem *_ConstructRankListItem(string name, int score);

static int _ScoreComparer(void *item1, void *item2);

typedef struct {
    int score;
    unsigned int life;
    unsigned int remainingPellets;
} GameState;

static Difficulty _difficulty;
static GameState _state = (GameState) {.life = 3, .score = 0};
static RankList _rank = EMPTY_LINKED_LIST;
static const GameObjectOption _options[] = {
        (GameObjectOption) {
                .playerSpeed = 1.,
                .ghostChasingSpeed = 0.5,
                .ghostChasedSpeed = 0.4,
                .ghostChasedCountDown = 10000,
                .ghostPathfindingInterval = 2000,
        },
        (GameObjectOption) {
                .playerSpeed = 1.,
                .ghostChasingSpeed = 0.7,
                .ghostChasedSpeed = 0.6,
                .ghostChasedCountDown = 10000,
                .ghostPathfindingInterval = 1500,
        },
        (GameObjectOption) {
                .playerSpeed = 1.,
                .ghostChasingSpeed = 0.9,
                .ghostChasedSpeed = 0.8,
                .ghostChasedCountDown = 8000,
                .ghostPathfindingInterval = 1000
        }
};

void ResetGameState() {
    _state = (GameState) {.life = 3, .score = 0, .remainingPellets = 0};
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

void ChangeRemainingPellets(int change) {
    _state.remainingPellets += change;
}

unsigned int GetRemainingPellets() {
    return _state.remainingPellets;
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

void InitGameController() {
    SetWindowTitle("PAC SUPERMAN!");
    _ReadRankList();
}

static inline bool _WriteRankList() {
    FILE *fp = fopen(RANK_FILE, "wb");
    if (!fp) return false;
    for (RankListNode *node = _rank.head; node != NULL; node = node->next) {
        fwrite(node->element, sizeof(RankListItem), 1, fp);
    }
    if (fclose(fp)) return false;
    return true;
}

static inline bool _ReadRankList() {
    FILE *fp = fopen(RANK_FILE, "rb");
    if (!fp) return false;
    while (!feof(fp)) {
        RankListItem *item = malloc(sizeof(RankListItem));
        if (fread(item, sizeof(RankListItem), 1, fp) != 1) break;
        ListAddElement(&_rank, item);
    }
    if (fclose(fp)) return false;
    return true;
}

static inline RankListItem *_ConstructRankListItem(string name, int score) {
    RankListItem *obj = malloc(sizeof(RankListItem));
    obj->score = score;
    strcpy_s(obj->name, MAX_NAME_LENGTH, name);
    return obj;
}

RankList GetRank() {
    return _rank;
}

static int _ScoreComparer(void *item1, void *item2) {
    return ((RankListItem *) item2)->score - ((RankListItem *) item1)->score;
}

bool AddToRank(string name, int score) {
    OrderedListAddElement(&_rank, _ConstructRankListItem(name, score), _ScoreComparer);
    if (_rank.length > MAX_RANK_LENGTH) free(ListPopElement(&_rank)); // 移除最后一名
    return _WriteRankList();
}

void EndGame(EndGameResult result) {
    PauseGame();
    RankListItem *last = ListGetLastElement(&_rank);
    unsigned int score = _state.score;
    if (result == WIN && (!last || _rank.length < MAX_RANK_LENGTH || score > last->score)) result = NEW_RECORD;
    AddUISprite(GetCurrentScene(), ConstructEndGameBoxSprite(result));
}