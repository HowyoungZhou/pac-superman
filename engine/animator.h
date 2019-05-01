#ifndef PAC_SUPERMAN_ANIMATOR_H
#define PAC_SUPERMAN_ANIMATOR_H

#include <stdint.h>
#include <stdbool.h>

struct sprite;
typedef struct sprite Sprite;

struct animator;
typedef struct animator Animator;

typedef uint16_t Frame;

struct animator {
    Frame currentFrame;
    Frame framesCount;
    double interval;
    bool repeated;
    bool reverse;
    bool paused;

    void (*Animate)(Animator *this, Sprite *sprite, Frame frame);

    int intervals[];
};

Animator *ConstructAnimator(Frame framesCount);

void DestructAnimator(Animator *this);

void PauseAnimator(Animator *this);

void ResumeAnimator(Animator *this);

void ResetAnimator(Animator *this);

void TickAnimator(Animator *this, double interval);

Frame GetActualFrame(Animator *this);

#endif //PAC_SUPERMAN_ANIMATOR_H
