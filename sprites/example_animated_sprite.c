#include <sprite.h>
#include <extgraph.h>
#include <drawing.h>
#include <animator.h>
#include "example_animated_sprite.h"

static void _AnimateExampleSprite(Animator *this, Sprite *sprite, uint16_t frame, double interval);

static void _AnimateExampleSprite(Animator *this, Sprite *sprite, uint16_t frame, double interval) {
    StartFilledRegion((frame + 1) / 5.);
    DrawVectorRectangle(sprite->position, sprite->size);
    EndFilledRegion();
}

Sprite *ConstructExampleAnimatedSprite() {
    Sprite *obj = ConstructSprite((Vector2) {0, 0.5}, (Vector2) {0.5, 0.5}, (Vector2) {0, 0});
    obj->hasAnimation = true;
    Animator *animator = ConstructAnimator(5);
    obj->renderer.animator = animator;
    animator->reverse = true;
    for (int i = 0; i < 5; i++)
        animator->intervals[i] = 100;
    animator->Animate = _AnimateExampleSprite;
    return obj;
}