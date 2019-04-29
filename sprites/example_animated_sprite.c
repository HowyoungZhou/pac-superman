#include <sprite.h>
#include <extgraph.h>
#include <drawing.h>
#include <animator.h>
#include "example_animated_sprite.h"

static void _AnimateExampleSprite(Animator *this, Sprite *sprite, frame frame);

static void _AnimateExampleSprite(Animator *this, Sprite *sprite, frame frame) {
    StartFilledRegion(0);
    DrawVectorRectangle(sprite->position, VMultiply((frame + 1) / 5., sprite->size));
    EndFilledRegion();
}

Sprite *ConstructExampleAnimatedSprite() {
    Sprite *obj = ConstructSprite((Vector2) {0, 0.5}, (Vector2) {0.5, 0.5}, (Vector2) {0, 0});
    obj->hasAnimation = true;
    Animator *animator = ConstructAnimator(5);
    obj->renderer.animator = animator;
    animator->reverse = true;
    for (int i = 0; i < 5; i++)
        animator->intervals[i] = 1000;
    animator->Animate = _AnimateExampleSprite;
    return obj;
}
