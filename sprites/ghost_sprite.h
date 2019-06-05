#ifndef PAC_SUPERMAN_GHOST_H
#define PAC_SUPERMAN_GHOST_H

#include <assets.h>

typedef enum {
    UP, RIGHT, DOWN, LEFT
} Direction;

typedef enum {
    CHASING, CHASED_AFTER, EATEN
} GhostState;

typedef struct {
    Vector2 initPos;
    BitmapAsset *assets[8];
    Direction lookingAt;
    GhostState state;
} Ghost;

Sprite *ConstructGhostSprite(Vector2 position, Vector2 size, string name);

#endif //PAC_SUPERMAN_GHOST_H
