#ifndef PAC_SUPERMAN_GAME_STATE_H
#define PAC_SUPERMAN_GAME_STATE_H

#define MAX_NAME_LENGTH 100
#define RANK_FILE "rank.dat"
#define MAX_RANK_LENGTH 5
#define MAX_SCORE_LENGTH 8

typedef enum {
    EASY = 0, NORMAL, HARD
} Difficulty;

typedef struct {
    double playerSpeed;
    double ghostChasingSpeed;
    double ghostChasedSpeed;
    double ghostChasedCountDown;
    double ghostPathfindingInterval;
} GameObjectOption;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int score;
} RankListItem;

typedef enum {
    LOSE, WIN, NEW_RECORD
} EndGameResult;

typedef LinkedList RankList;
typedef LinkedListNode RankListNode;

/**@brief 重置游戏状态。
 *
 */
void ResetGameState();

/**@brief 增减生命。
 *
 * @param change 生命变化，正数表示增加，负数表示减小
 */
void ChangeLife(int change);

/**@brief 获取生命。
 *
 * @return 当前生命
 */
unsigned int GetLife();

/**@brief 修改分数值。
 *
 * @param change 分数变化，正数表示增加，负数表示减小
 */
void ChangeScore(int change);

/**@brief 获取分数值。
 *
 * @return 当前分数
 */
int GetScore();

/**@brief 修改剩余豆子数量。
 *
 * @param change 剩余豆子数量变化，正数表示增加，负数表示减小
 */
void ChangeRemainingPellets(int change);

/**@brief 获取剩余豆子数量。
 *
 * @return 剩余豆子数量
 */
unsigned int GetRemainingPellets();

/**@brief 获取难度。
 *
 * @return 当前难度
 */
Difficulty GetDifficulty();

/**@brief 设置难度。
 *
 * @param difficulty 新的难度
 */
void SetDifficulty(Difficulty difficulty);

/**@brief 获取游戏物体配置。
 *
 * @return 游戏物体配置
 */
GameObjectOption GetGameObjectOption();

/**@brief 初始化游戏控制器。
 *
 */
void InitGameController();

/**@brief 获取排行榜。
 *
 * @return 排行榜列表
 */
RankList GetRank();

/**@brief 向排行榜中增加条目。
 *
 * @param name 玩家姓名
 * @param score 玩家分数
 * @return 如添加成功则返回 true，否则返回 false。
 */
bool AddToRank(string name, int score);

/**@brief 游戏结束，当游戏胜利或失败时调用。
 *
 * @param result 游戏结果（LOSE 或 WIN）
 */
void EndGame(EndGameResult result);

#endif //PAC_SUPERMAN_GAME_STATE_H
