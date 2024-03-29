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

static inline void _ClearScreen(string backColor);

static inline void _ForEachSprite(SpritesList *list, ForEachSpriteCallback callback);

static inline void _UpdateScene();

static void _UpdateTimers(Sprite *sprite);

static void _UpdateSprite(Sprite *sprite);

static void _AutoNav(Sprite *sprite);

static inline Collider _CalcAbsoluteCollider(Sprite *sprite, Collider *collider);

static inline void _DetectSpriteCollision(Sprite *s1, Sprite *s2);

static void _DetectCollision(Scene *current);

static void _UpdatePosition(Sprite *sprite);

static void _UpdateAnimator(Sprite *sprite);

static void _RenderSprite(Sprite *sprite);

static inline double _UpdateInterval();

static void _MainTimerHandler(int timerID);

static inline void _RemoveSprites(Scene *current);

extern exception NullArgumentException;
extern exception MethodNotImplementedException;

static LARGE_INTEGER _frequency;
static LARGE_INTEGER _lastUpdated;
static double _interval;

static SceneStack _scenes = EMPTY_LINKED_LIST;
static Scene *_newScene = NULL;
static bool _popScene = false;
static bool _paused = false;
static SpritesList _gameSpritesToBeRemoved = EMPTY_LINKED_LIST;
static SpritesList _uiSpritesToBeRemoved = EMPTY_LINKED_LIST;

void InitEngine() {
    RegisterTimerEvent(_MainTimerHandler);
    // 记录当前时间戳
    QueryPerformanceFrequency(&_frequency);
    QueryPerformanceCounter(&_lastUpdated);
    startTimer(RENDERER_TIMER_ID, RENDERER_TIMER_INTERVAL);
    startTimer(PHYSICAL_ENGINE_TIMER_ID, PHYSICAL_ENGINE_TIMER_INTERVAL);
    _InitUI();
    ChangePathfindingBorder(ZERO_VECTOR, (Vector2) {GetWindowWidth(), GetWindowHeight()});
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

Scene *GetCurrentScene() {
    return ListGetLastElement(&_scenes);
}

void PushScene(Scene *scene) {
    scene->Initialize(scene);
    ListAddElement(&_scenes, scene);
}

void PopScene() {
    _popScene = true;
}

bool ReplaceScene(Scene *newScene) {
    if (_newScene != NULL) return false;
    _popScene = true;
    _newScene = newScene;
    return true;
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
    _UpdateScene(); // 检测有无场景更新
    Scene *current = (Scene *) ListGetLastElement(&_scenes);
    if (current) _RemoveSprites(current);
    switch (timerID) {
        case RENDERER_TIMER_ID:
            if (current == NULL) {
                _ClearScreen("Black"); // 无场景时显示黑色背景
                break;
            }
            _ClearScreen(current->backColor);
            _ForEachSprite(&current->gameSprites, _RenderSprite);
            _ForEachSprite(&current->uiSprites, _RenderSprite);
            break;
        case PHYSICAL_ENGINE_TIMER_ID:
            if (current == NULL) break;
            _UpdateInterval();
            _ForEachSprite(&current->gameSprites, _UpdateTimers); // 更新计时器
            _ForEachSprite(&current->uiSprites, _UpdateTimers);
            _ForEachSprite(&current->gameSprites, _UpdateAnimator); // 更新动画器
            _ForEachSprite(&current->gameSprites, _UpdateSprite); // 调用 Sprite 的 Update 函数
            _ForEachSprite(&current->gameSprites, _AutoNav);
            _DetectCollision(current); // 碰撞检测
            _ForEachSprite(&current->gameSprites, _UpdatePosition); // 更新位置
            break;
        default:
            break;
    }
}

static inline void _UpdateScene() {
    if (!_popScene) return;
    // 弹出当前场景
    Scene *scene = ListPopElement(&_scenes);
    if (scene != NULL) scene->Destruct(scene);
    // 如果有新场景则加载新场景
    if (_newScene != NULL) {
        PushScene(_newScene);
        _newScene = NULL;
    }
    _popScene = false;
}

static void _UpdateTimers(Sprite *sprite) {
    for (LinkedListNode *node = sprite->timers.head; node != NULL; node = node->next) {
        Timer *timer = node->element;
        if (!timer->enable) continue;
        timer->currentTick += _interval;
        if (timer->currentTick >= timer->interval) {
            timer->callback(sprite);
            timer->currentTick = 0;
        }
    }
}

static void _UpdateSprite(Sprite *sprite) {
    if (sprite->Update == NULL)return;
    sprite->Update(sprite, _interval);
}

static void _AutoNav(Sprite *sprite) {
    if (sprite->navAgent.path) AutoNav(sprite, _interval);
}

static inline Collider _CalcAbsoluteCollider(Sprite *sprite, Collider *collider) {
    Collider res = *collider;
    Vector2 position = VAdd(sprite->position, VMultiply(_interval / 1000.0, sprite->velocity));
    switch (res.type) {
        case BOX_COLLIDER:
            res.shape.boxCollider.position = VAdd(position, res.shape.boxCollider.position);
            break;
        case CIRCLE_COLLIDER:
            res.shape.circleCollider.centre = VAdd(position, res.shape.circleCollider.centre);
            break;
    }
    return res;
}

static inline void _DetectSpriteCollision(Sprite *s1, Sprite *s2) {
    if (s1->colliders.head == NULL || s2->colliders.head == NULL)return;
    for (ColliderNode *n1 = s1->colliders.head; n1 != NULL; n1 = n1->next) {
        Collider c1 = _CalcAbsoluteCollider(s1, (Collider *) n1->element);
        for (ColliderNode *n2 = s2->colliders.head; n2 != NULL; n2 = n2->next) {
            Collider c2 = _CalcAbsoluteCollider(s2, (Collider *) n2->element);
            if (!DetectIntersection(&c1, &c2)) continue;
            if (s1->Collide != NULL) {
                s1->Collide(s1, ((Collider *) n1->element)->id, s2);
                return;
            }
            if (s2->Collide != NULL) {
                s2->Collide(s2, ((Collider *) n2->element)->id, s1);
                return;
            }
        }
    }
}

static void _DetectCollision(Scene *current) {
    for (SpritesListNode *s1 = current->gameSprites.head; s1 != NULL; s1 = s1->next) {
        for (SpritesListNode *s2 = s1->next; s2 != NULL; s2 = s2->next) {
            if (((Sprite *) s1->element)->visible && ((Sprite *) s2->element)->visible)
                _DetectSpriteCollision(s1->element, s2->element);
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
}

static inline void _ClearScreen(string backColor) {
    SetPenColor(backColor);
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

static inline void _RemoveSprites(Scene *current) {
    if (_gameSpritesToBeRemoved.head != NULL) {
        for (SpritesListNode *node = _gameSpritesToBeRemoved.head; node != NULL; node = node->next) {
            _RemoveGameSprite(current, node->element);
        }
    }

    if (_uiSpritesToBeRemoved.head != NULL) {
        for (SpritesListNode *node = _uiSpritesToBeRemoved.head; node != NULL; node = node->next) {
            _RemoveUISprite(current, node->element);
        }
    }

    ClearList(&_gameSpritesToBeRemoved, NULL);
    ClearList(&_uiSpritesToBeRemoved, NULL);
}

void RemoveGameSpriteFromCurrentScene(Sprite *sprite) {
    ListAddElement(&_gameSpritesToBeRemoved, sprite);
}

void RemoveUISpriteFromCurrentScene(Sprite *sprite) {
    ListAddElement(&_uiSpritesToBeRemoved, sprite);
}
