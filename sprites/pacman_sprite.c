#include <sprite.h>
#include <vector2.h>
#include <extgraph.h>
#include <drawing.h>
#include <animator.h>
#include <controller.h>
#include <game_scene.h>
#include "pacman_sprite.h"

#define ANGLE 30
#define SPEED 1

static int direction = 0;

static void _AnimatedPacmanSprite(Animator *this, Sprite *sprite, Frame frame);

static void _Update(Sprite *this, double interval);

static void _AnimatedPacmanSprite(Animator *this, Sprite *sprite, Frame frame) {
    double _angle;
    double size = CalcIncircleRadius(sprite) * 2;

    StartFilledRegion(1.);
    if (sprite->velocity.x > 0) {
        direction = 0;
    } else if (sprite->velocity.y > 0) {
        direction = 1;
    } else if (sprite->velocity.x < 0) {
        direction = 2;
    } else if (sprite->velocity.y < 0) {
        direction = 3;
    }
    _angle = frame * ANGLE / 4 + direction * 90;
    TurnPolarAngleTo(_angle);
    MovePen(sprite->position.x + sprite->size.x / 2, sprite->position.y + sprite->size.y / 2);
    MovePolarPen(size / 2);
    DrawArc((size) / 2, _angle, 360 - frame * ANGLE / 2);
    TurnPolarAngle(180 - frame * ANGLE / 2);
    DrawPolarLine(size / 2);
    TurnPolarAngle(frame * ANGLE / 2 - 180);
    DrawPolarLine(size / 2);
    EndFilledRegion();
}

static void _Update(Sprite *this, double interval) {
    // 通过 Controller 更新速度
    this->velocity = VMultiply(SPEED, GetNormalizedControllerVector());
}

Sprite *ConstructPacmanSprite(Vector2 position, Vector2 size, string color) {
    Sprite *obj = ConstructSprite(position, size, ZERO_VECTOR);

    Animator *animator = ConstructAnimator(5);
    for (int i = 0; i < 5; i++) animator->intervals[i] = 80;
    animator->reverse = true;
    animator->Animate = _AnimatedPacmanSprite;

    obj->name = "PacMan";
    obj->hasAnimation = true;
    obj->renderer.animator = animator;
    obj->Update = _Update;
    obj->foreColor = color;
    RegisterCircleCollider(obj, DEFAULT_COLLIDER_ID, true, CalcRelativeCentre(obj), CalcIncircleRadius(obj));
    GetCurrentHeroes()->pacman = obj;
    return obj;
}




