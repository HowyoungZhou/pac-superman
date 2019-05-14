#include <sprite.h>
#include <vector2.h>
#include <extgraph.h>
#include <drawing.h>
#include <animator.h>
#include <controller.h>
#include "pacman_sprite.h"

#define ANGLE 30
#define DIRECTION 0
#define PACMAN_SIZE 0.5
#define SPEED 1

static void _AnimatedPacmanSprite(Animator *this, Sprite *sprite, Frame frame);

static void _Update(Sprite *this, double interval);

static void _AnimatedPacmanSprite(Animator *this, Sprite *sprite, Frame frame) {
    double _angle;

    StartFilledRegion(0);
    _angle = frame * ANGLE / 4 + DIRECTION * ANGLE * 3;
    TurnPolarAngleTo(_angle);
    MovePen(sprite->position.x+sprite->size.x/2, sprite->position.y+sprite->size.y/2);
    MovePolarPen(PACMAN_SIZE / 2);
    DrawArc((PACMAN_SIZE) / 2, _angle, 360 - frame * ANGLE / 2);
    TurnPolarAngle(180 - frame * ANGLE / 2);
    DrawPolarLine(PACMAN_SIZE / 2);
    TurnPolarAngle(frame * ANGLE / 2 - 180);
    DrawPolarLine(PACMAN_SIZE / 2);

    EndFilledRegion();
}

static void _Update(Sprite *this, double interval) {
    // 通过 Controller 更新速度
    this->velocity = VMultiply(SPEED, GetNormalizedControllerVector());
}

Sprite *ConstructPacmanSprite() {
    Sprite *obj = ConstructSprite((Vector2) {0, 0.5}, (Vector2) {0.5, 0.5}, (Vector2) {0, 0});
    obj->hasAnimation = true;
    Animator *animator = ConstructAnimator(5);
    obj->renderer.animator = animator;
    animator->reverse = true;
    for (int i = 0; i < 5; i++)
        animator->intervals[i] = 80;
    animator->Animate = _AnimatedPacmanSprite;
    obj->Update = _Update;
    RegisterCircleCollider(obj, DEFAULT_COLLIDER_ID, true, CalcRelativeCentre(obj), CalcIncircleRadius(obj));
    return obj;
}




