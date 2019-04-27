#ifndef PAC_SUPERMAN_SPRITE_H
#define PAC_SUPERMAN_SPRITE_H

#include <stdbool.h>
#include "vector2.h"
#include "animator.h"

struct sprite;
typedef struct sprite Sprite;

struct sprite {
    Vector2 position;
    Vector2 size;
    Vector2 velocity;
    bool visible;
    bool collidable;
    bool solid;
    bool hasAnimation;

    union {
        void (*Render)(Sprite *this, double interval);

        Animator *animator;
    } renderer;

    void (*Destruct)(Sprite *this);
};

Sprite *ConstructSprite(Vector2 position, Vector2 size, Vector2 velocity);

#endif //PAC_SUPERMAN_SPRITE_H
