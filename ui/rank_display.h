#ifndef PAC_SUPERMAN_RANK_DISPLAY_H
#define PAC_SUPERMAN_RANK_DISPLAY_H

#include <sprite.h>

typedef struct GameResult{
    char *name;
    char *score;
}GameResult;

Sprite *ConstructRankDisplaySprite();

#endif //PAC_SUPERMAN_RANK_DISPLAY_H
