#include <extgraph.h>
#include <exception.h>
#include <profileapi.h>
#include <linked_list.h>
#include <imgui.h>
#include "engine.h"
#include "sprite.h"
#include "drawing.h"

typedef void (*ForEachSpriteCallback)(Sprite *sprite);

static inline void _InitUI();

static inline void _ClearScreen();

static inline void _ForEachSprite(LinkedList *list, ForEachSpriteCallback callback);

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

static LinkedList _spritesList = {NULL, NULL, 0};
static LinkedList _uiSpritesList = {NULL, NULL, 0};

void InitEngine() {
    registerTimerEvent(_MainTimerHandler);
    QueryPerformanceFrequency(&_frequency);
    QueryPerformanceCounter(&_lastUpdated);
    startTimer(RENDERER_TIMER_ID, RENDERER_TIMER_INTERVAL);
    startTimer(PHYSICAL_ENGINE_TIMER_ID, PHYSICAL_ENGINE_TIMER_INTERVAL);
    _InitUI();
}

void RegisterSprite(Sprite *sprite) {
    AddElement(&_spritesList, sprite);
}

void RegisterUISprite(Sprite *uiSprite) {
    AddElement(&_uiSpritesList, uiSprite);
}

void PauseGame() {
    cancelTimer(PHYSICAL_ENGINE_TIMER_ID);
}

void ResumeGame() {
    startTimer(PHYSICAL_ENGINE_TIMER_ID, PHYSICAL_ENGINE_TIMER_INTERVAL);
}

static inline void _InitUI() {
    registerMouseEvent(uiGetMouse);
    registerKeyboardEvent(uiGetKeyboard);
    registerCharEvent(uiGetChar);
}

static inline void _ForEachSprite(LinkedList *list, ForEachSpriteCallback callback) {
    for (LinkedListNode *node = list->head; node != NULL; node = node->next) {
        callback(node->element);
    }
}

static void _MainTimerHandler(int timerID) {
    switch (timerID) {
        case RENDERER_TIMER_ID:
            _ClearScreen();
            _ForEachSprite(&_spritesList, _RenderSprite);
            _ForEachSprite(&_uiSpritesList, _RenderSprite);
            break;
        case PHYSICAL_ENGINE_TIMER_ID:
            _GetInterval();
            _ForEachSprite(&_spritesList, _UpdateAnimator);
            _ForEachSprite(&_spritesList, _UpdateSprite);
            _DetectCollision();
            _ForEachSprite(&_spritesList, _UpdatePosition);
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
    for (LinkedListNode *s1 = _spritesList.head; s1 != NULL; s1 = s1->next) {
        for (LinkedListNode *s2 = s1->next; s2 != NULL; s2 = s2->next) {
            DetectCollision(s1->element, s2->element, _interval);
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
    SaveGraphicsState();
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
    RestoreGraphicsState();
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
