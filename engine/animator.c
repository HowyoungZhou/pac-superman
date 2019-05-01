#include <stdlib.h>
#include <exception.h>
#include <time.h>
#include "animator.h"
#include "sprite.h"

void TickAnimator(Animator *this, double interval) {
    // 计算真实帧数并调用 Animate() 方法
    const Frame frame = GetActualFrame(this);

    // 如暂停则不更新计时器
    if (this->paused)return;

    // 更新计时器并判断是否达到或超过了当前帧间隔
    this->interval += interval;
    if (this->interval < this->intervals[frame])return;

    // 如已到达最后一帧且不循环则暂停动画器
    if (this->currentFrame >= this->framesCount - 1 && !this->repeated) {
        PauseAnimator(this);
        this->interval = 0;
        return;
    }

    // 如当前间隔达到或超过了当前帧间隔，则跳转到下一帧并重置计时器
    this->interval = this->interval - this->intervals[frame];
    this->currentFrame++;

    // 如当前帧已达到两倍的帧总数（即达到了正反向动画的帧数总和）则重置动画器，从第一帧开始播放
    if (this->currentFrame >= 2 * this->framesCount) {
        ResetAnimator(this);
    }
}

Frame GetActualFrame(Animator *this) {
    Frame currentFrame = this->currentFrame;
    Frame framesCount = this->framesCount;
    bool reverse = this->reverse;
    if (currentFrame < framesCount)return currentFrame;
    if (reverse) return 2 * framesCount - 1 - currentFrame;
    else return currentFrame - framesCount;
}

void DestructAnimator(Animator *this) {
    free(this);
}

void PauseAnimator(Animator *this) {
    this->paused = true;
}

void ResumeAnimator(Animator *this) {
    this->paused = false;
}

void ResetAnimator(Animator *this) {
    this->interval = 0;
    this->currentFrame = 0;
}

Animator *ConstructAnimator(Frame framesCount) {
    Animator *obj = malloc(sizeof(Animator) + sizeof(int) * framesCount);
    obj->interval = 0;
    obj->currentFrame = 0;
    obj->repeated = true;
    obj->reverse = false;
    obj->paused = false;
    obj->framesCount = framesCount;
    obj->Animate = NULL;
    return obj;
}