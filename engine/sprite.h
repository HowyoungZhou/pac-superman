#ifndef PAC_SUPERMAN_SPRITE_H
#define PAC_SUPERMAN_SPRITE_H

#include <stdbool.h>
#include "vector2.h"
#include "animator.h"
#include "collider.h"

struct sprite;
typedef struct sprite Sprite;

struct sprite {
    Vector2 position;
    Vector2 size;
    Vector2 velocity;
    bool visible;
    bool hasAnimation;

    union {
        void (*Render)(Sprite *this);

        Animator *animator;
    } renderer;

    CollidersList colliders;

    void (*Update)(Sprite *this, double interval);

    void (*Collide)(Sprite *this, int id, Sprite *other);

    void (*Destruct)(Sprite *this);
};

Sprite *ConstructSprite(Vector2 position, Vector2 size, Vector2 velocity);

void RegisterCollider(Sprite *sprite, Collider collider);

bool UnregisterCollider(Sprite *sprite, int id);

void RegisterBoxCollider(Sprite *sprite, int id, bool solid, Vector2 size, Vector2 position);

void RegisterCircleCollider(Sprite *sprite, int id, bool solid, Vector2 centre, double radius);

Vector2 CalcCentre(Sprite *sprite);

Vector2 CalcRelativeCentre(Sprite *sprite);

double CalcIncircleRadius(Sprite *sprite);

#endif //PAC_SUPERMAN_SPRITE_H
