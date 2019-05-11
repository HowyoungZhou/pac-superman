#include <extgraph.h>
#include <exception.h>
#include <profileapi.h>
#include <imgui.h>
#include <events.h>
#include "engine.h"
#include "sprite.h"
#include "drawing.h"
#include "scene.h"

typedef void (*ForEachSpriteCallback)(Sprite *sprite);

static void _uiGetChar(char c);

static inline void _InitUI();

static inline void _ClearScreen(Scene *current);

static inline void _ForEachSprite(SpritesList *list, ForEachSpriteCallback callback);

static void _UpdateSprite(Sprite *sprite);

static void _DetectCollision(Scene *current);

static void _UpdatePosition(Sprite *sprite);

static void _UpdateAnimator(Sprite *sprite);

static void _RenderSprite(Sprite *sprite);

static inline double _UpdateInterval();

static void _MainTimerHandler(int timerID);

extern exception NullArgumentException;
extern exception MethodNotImplementedException;

static LARGE_INTEGER _frequency;
static LARGE_INTEGER _lastUpdated;
static double _interval;

static SceneStack _scenes = EMPTY_LINKED_LIST;
static bool _paused = false;

void InitEngine() {
    RegisterTimerEvent(_MainTimerHandler);
    // 记录当前时间戳
    QueryPerformanceFrequency(&_frequency);
    QueryPerformanceCounter(&_lastUpdated);
    startTimer(RENDERER_TIMER_ID, RENDERER_TIMER_INTERVAL);
    startTimer(PHYSICAL_ENGINE_TIMER_ID, PHYSICAL_ENGINE_TIMER_INTERVAL);
    _InitUI();
}

void PauseGame() {
    // 停止物理引擎更新
    cancelTimer(PHYSICAL_ENGINE_TIMER_ID);
    _paused = true;
}

void ResumeGame() {
    _UpdateInterval();
    startTimer(PHYSICAL_ENGINE_TIMER_ID, PHYSICAL_ENGINE_TIMER_INTERVAL);
    _paused = false;
}

bool IsPaused() {
    return _paused;
}

void PushScene(Scene *scene) {
    scene->Initialize(scene);
    AddElement(&_scenes, scene);
}

static void _uiGetChar(char c) {
    uiGetChar(c);
}

static inline void _InitUI() {
    RegisterMouseEvent(uiGetMouse);
    RegisterKeyboardEvent(uiGetKeyboard);
    RegisterCharEvent(_uiGetChar);
}

static inline void _ForEachSprite(SpritesList *list, ForEachSpriteCallback callback) {
    for (SpritesListNode *node = list->head; node != NULL; node = node->next) {
        callback(node->element);
    }
}

static void _MainTimerHandler(int timerID) {
    Scene *current = (Scene *) _scenes.tail->element;
    switch (timerID) {
        case RENDERER_TIMER_ID:
            _ClearScreen(current);
            _ForEachSprite(&current->gameSprites, _RenderSprite);
            _ForEachSprite(&current->uiSprites, _RenderSprite);
            break;
        case PHYSICAL_ENGINE_TIMER_ID:
            _UpdateInterval();
            _ForEachSprite(&current->gameSprites, _UpdateAnimator); // 更新动画器
            _ForEachSprite(&current->gameSprites, _UpdateSprite); // 调用 Sprite 的 Update 函数
            _DetectCollision(current); // 碰撞检测
            _ForEachSprite(&current->gameSprites, _UpdatePosition); // 更新位置
            break;
        default:
            break;
    }
}

static void _UpdateSprite(Sprite *sprite) {
    if (sprite->Update == NULL)return;
    sprite->Update(sprite, _interval);
}

static void _DetectCollision(Scene *current) {
    for (SpritesListNode *s1 = current->gameSprites.head; s1 != NULL; s1 = s1->next) {
        for (SpritesListNode *s2 = s1->next; s2 != NULL; s2 = s2->next) {
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
    SaveGraphicsState(); // 保存当前图形库状态避免不同 Sprite 之间干扰
    MovePen(sprite->position.x, sprite->position.y);
    SetPenColor(sprite->foreColor);
    // 如果 Sprite 有动画则渲染动画
    if (sprite->hasAnimation) {
        Animator *animator = sprite->renderer.animator;
        if (animator->Animate == NULL)raise(MethodNotImplementedException);
        Frame frame = GetActualFrame(animator);
        animator->Animate(animator, sprite, frame);
    } else {
        if (sprite->renderer.Render == NULL)raise(MethodNotImplementedException);
        sprite->renderer.Render(sprite);
    }
    RestoreGraphicsState(); // 恢复图形库状态
}

static inline void _ClearScreen(Scene *current) {
    SetPenColor(current->backColor);
    StartFilledRegion(1.);
    DrawRectangle(0, 0, GetWindowWidth(), GetWindowHeight());
    EndFilledRegion();
}

static inline double _UpdateInterval() {
    LARGE_INTEGER timestamp;
    QueryPerformanceCounter(&timestamp);
    _interval = (timestamp.QuadPart - _lastUpdated.QuadPart) * 1000.0 / _frequency.QuadPart;
    _lastUpdated = timestamp;
    QueryPerformanceFrequency(&_frequency);
}
