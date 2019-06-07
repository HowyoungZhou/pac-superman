/**@file engine.h
 * @brief 该文件包含了游戏引擎的相关方法。
 */
#ifndef PAC_SUPERMAN_ENGINE_H
#define PAC_SUPERMAN_ENGINE_H

#include "sprite.h"
#include "scene.h"

#define RENDERER_TIMER_ID 0
#define PHYSICAL_ENGINE_TIMER_ID 1
#define RENDERER_TIMER_INTERVAL 5
#define PHYSICAL_ENGINE_TIMER_INTERVAL 1

typedef LinkedList SceneStack;
typedef LinkedListNode SpritesListNode;

/**@brief 初始化游戏引擎。
 *
 */
void InitEngine();

/**@brief 暂停游戏，位置更新和碰撞检测将会被暂停，但 UI 并不会受到影响。
 *
 */
void PauseGame();

/**@brief 继续游戏。
 *
 */
void ResumeGame();

/**@brief 获取当前游戏状态，即是否被暂停。
 *
 * @return 如果游戏被暂停则返回 true
 */
bool IsPaused();

/**@brief 获取当前场景，即 Scenes 栈栈顶场景。
 *
 * @return 如 Scenes 栈非空则返回当前场景，否则返回 NULL
 */
Scene *GetCurrentScene();

/**@brief 将新的 Scene 加入当前的 Scenes 栈。
 *
 * @param scene Scene 对象
 */
void PushScene(Scene *scene);

/**@brief 将当前场景从当前的 Scenes 栈中弹出。
 *
 * 注意：该方法可在一个渲染周期内被安全调用（通常为 Render, Animate 或 Update 方法中），然而在一个渲染周期内只允许弹出一个场景。
 * 当在一个渲染周期多次调用该方法时只会弹出一个场景。
 */
void PopScene();

/**@brief 用新场景替换当前场景。
 *
 * 注意：该方法可在一个渲染周期内被安全调用（通常为 Render, Animate 或 Update 方法中），然而在一个渲染周期内只允许替换一个场景。
 * 当在一个渲染周期内第二次或更多次调用该方法时会失败并返回 false，请注意妥善处理未成功替换的场景（如调用析构函数）。
 *
 * @param newScene 新场景
 * @return 是否成功替换场景
 */
bool ReplaceScene(Scene *newScene);

/**@brief 从当前场景移除游戏 Sprite。
 *
 * @param sprite 要移除的 Sprite
 */
void RemoveGameSpriteFromCurrentScene(Sprite *sprite);

/**@brief 从当前场景移除 UI Sprite。
 *
 * @param sprite 要移除的 Sprite
 */
void RemoveUISpriteFromCurrentScene(Sprite *sprite);

#endif //PAC_SUPERMAN_ENGINE_H
