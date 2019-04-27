#ifndef PAC_SUPERMAN_ANIMATOR_H
#define PAC_SUPERMAN_ANIMATOR_H

#include <stdint.h>
#include <stdbool.h>

struct sprite;
typedef struct sprite Sprite;

struct animator;
typedef struct animator Animator;

struct animator {
    uint16_t currentFrame;
    uint16_t framesCount;
    double interval;
    bool repeated;
    bool reverse;
    bool paused;

    void (*Animate)(Animator *this, Sprite *sprite, uint16_t frame, double interval);

    int intervals[];
};

Animator *ConstructAnimator(uint16_t framesCount);

void DestructAnimator(Animator *this);

void PauseAnimator(Animator *this);

void ResumeAnimator(Animator *this);

void ResetAnimator(Animator *this);

void TickAnimator(Animator *this, Sprite *sprite, double interval);

#endif //PAC_SUPERMAN_ANIMATOR_H
