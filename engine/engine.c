#include <stdio.h>
#include <extgraph.h>
#include <exception.h>
#include <profileapi.h>
#include "engine.h"
#include "sprite.h"
#include "sprites_list.h"
#include "drawing.h"

static void _ClearScreen();

static void _UpdatePosition(Sprite *sprite);

static void _RenderSprite(Sprite *sprite);

static inline double _GetInterval();

static LARGE_INTEGER _frequency;
static LARGE_INTEGER _lastUpdated;
static double _interval;

void InitEngine() {
    QueryPerformanceFrequency(&_frequency);
    QueryPerformanceCounter(&_lastUpdated);
}

void MainTimerHandler(int timerID) {
    _GetInterval();
    //TODO: 碰撞检测
    ForEachSprite(_UpdatePosition);
    _ClearScreen();
    ForEachSprite(_RenderSprite);
}

static void _UpdatePosition(Sprite *sprite) {
    sprite->position = Vector2Add(sprite->position, Vector2Multiply(_interval, sprite->velocity));
}

static void _RenderSprite(Sprite *sprite) {
    if (!sprite->visible)return;
    extern exception NullArgumentException;
    extern exception MethodNotImplementedException;
    if (sprite->hasAnimation) {
        Animator *animator = sprite->renderer.animator;
        if (animator == NULL)raise(NullArgumentException);
        TickAnimator(animator, sprite, _interval);
    } else {
        if (sprite->renderer.Render == NULL)raise(MethodNotImplementedException);
        sprite->renderer.Render(sprite, _interval);
    }
}

static void _ClearScreen() {
    SetEraseMode(TRUE);
    StartFilledRegion(1.);
    DrawRectangle(0, 0, GetWindowWidth(), GetWindowHeight());
    EndFilledRegion();
    SetEraseMode(FALSE);
}

static inline double _GetInterval() {
    LARGE_INTEGER timestamp;
    QueryPerformanceCounter(&timestamp);
    _interval = (timestamp.QuadPart - _lastUpdated.QuadPart) * 1000.0 / _frequency.QuadPart;
    _lastUpdated = timestamp;
    QueryPerformanceFrequency(&_frequency);
}
