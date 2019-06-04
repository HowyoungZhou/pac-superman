#ifndef PAC_SUPERMAN_GHOST_H
#define PAC_SUPERMAN_GHOST_H

#include <assets.h>

typedef enum {
    UP, RIGHT, DOWN, LEFT
} Direction;

typedef struct {
    BitmapAsset *assets[10];
    Direction lookingAt;
    bool chasedAfter;
} Ghost;

#endif //PAC_SUPERMAN_GHOST_H
