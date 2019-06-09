#ifndef PAC_SUPERMAN_RANK_DISPLAY_H
#define PAC_SUPERMAN_RANK_DISPLAY_H

#include <sprite.h>

typedef struct GameResult{
    char *name;
    char *score;
}GameResult;

/**@brief RankDisplaySprite 构造函数
 *
 * @return RankDisplaySprite 对象
 */
Sprite *ConstructRankDisplaySprite();

#endif //PAC_SUPERMAN_RANK_DISPLAY_H
