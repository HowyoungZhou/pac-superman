#include <extgraph.h>
#include <exception.h>
#include <profileapi.h>
#include "engine.h"
#include "sprite.h"
#include "sprites_list.h"
#include "drawing.h"

static inline void _ClearScreen();

static void _UpdateSprite(Sprite *sprite);

static void _DetectCollision();

static void _UpdatePosition(Sprite *sprite);

static void _UpdateAnimator(Sprite *sprite);

static void _RenderSprite(Sprite *sprite);

static inline double _GetInterval();

static void _MainTimerHandler(int timerID);

extern exception NullArgumentException;
extern exception MethodNotImplementedException;

static LARGE_INTEGER _frequency;
static LARGE_INTEGER _lastUpdated;
static double _interval;

void InitEngine() {
    registerTimerEvent(_MainTimerHandler);
    QueryPerformanceFrequency(&_frequency);
    QueryPerformanceCounter(&_lastUpdated);
    startTimer(RENDERER_TIMER_ID, RENDERER_TIMER_INTERVAL);
    startTimer(PHYSICAL_ENGINE_TIMER_ID, PHYSICAL_ENGINE_TIMER_INTERVAL);
}

static void _MainTimerHandler(int timerID) {
    switch (timerID) {
        case RENDERER_TIMER_ID:
            _ClearScreen();
            ForEachSprite(_RenderSprite);
            break;
        case PHYSICAL_ENGINE_TIMER_ID:
            _GetInterval();
            ForEachSprite(_UpdateAnimator);
            ForEachSprite(_UpdateSprite);
            _DetectCollision();
            ForEachSprite(_UpdatePosition);
            break;
        default:
            break;
    }
}

static void _UpdateSprite(Sprite *sprite) {
    if (sprite->Update == NULL)return;
    sprite->Update(sprite, _interval);
}

static void _DetectCollision() {
    for (SpritesListNode *s1 = GetSpritesListHead(); s1 != NULL; s1 = s1->next) {
        for (SpritesListNode *s2 = s1->next; s2 != NULL; s2 = s2->next) {
            DetectCollision(s1->sprite, s2->sprite, _interval);
        }
    }
}

static void _UpdatePosition(Sprite *sprite) {
    sprite->position = VAdd(sprite->position, VMultiply(_interval / 1000.0, sprite->velocity));
}

static void _UpdateAnimator(Sprite *sprite) {
    if (!sprite->hasAnimation)return;
    Animator *animator = sprite->renderer.animator;
    if (animator == NULL)raise(NullArgumentException);
    TickAnimator(animator, _interval);
}

static void _RenderSprite(Sprite *sprite) {
    if (!sprite->visible)return;
    MovePen(sprite->position.x, sprite->position.y);
    if (sprite->hasAnimation) {
        Animator *animator = sprite->renderer.animator;
        if (animator->Animate == NULL)raise(MethodNotImplementedException);
        Frame frame = GetActualFrame(animator);
        animator->Animate(animator, sprite, frame);
    } else {
        if (sprite->renderer.Render == NULL)raise(MethodNotImplementedException);
        sprite->renderer.Render(sprite);
    }
}

static inline void _ClearScreen() {
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
