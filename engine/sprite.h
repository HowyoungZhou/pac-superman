#ifndef PAC_SUPERMAN_SPRITE_H
#define PAC_SUPERMAN_SPRITE_H

#include <stdbool.h>
#include "vector2.h"

struct sprite;
typedef struct sprite Sprite;

struct animator;
typedef struct animator Animator;

struct animator {
    unsigned int currentFrame;
    unsigned int *intervals;
    unsigned int framesCount;

    void (*Animate)(Sprite *this);
};

struct sprite {
    Vector2 position;
    Vector2 size;
    Vector2 velocity;
    bool collidable;
    bool solid;
    bool hasAnimation;

    union {
        void (*Render)(Sprite *this);

        Animator animator;
    } renderer;

    void (*Destruct)(Sprite *this);
};

void _DestructSprite(Sprite *this);

void _RenderSpriteDefault(Sprite *this);

Sprite *ConstructSprite(Vector2 position, Vector2 size, Vector2 velocity);

#endif //PAC_SUPERMAN_SPRITE_H
