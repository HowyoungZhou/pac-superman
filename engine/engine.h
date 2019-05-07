/**@file engine.h
 * @brief 该文件包含了游戏引擎的相关方法。
 */
#ifndef PAC_SUPERMAN_ENGINE_H
#define PAC_SUPERMAN_ENGINE_H

#include "sprite.h"

#define RENDERER_TIMER_ID 0
#define PHYSICAL_ENGINE_TIMER_ID 1
#define RENDERER_TIMER_INTERVAL 5
#define PHYSICAL_ENGINE_TIMER_INTERVAL 1

typedef LinkedList SpritesList;
typedef LinkedListNode SpritesListNode;

/**@brief 初始化游戏引擎
 *
 */
void InitEngine();

/**@brief 注册新的 Sprite，新的 Sprite 将会被渲染到屏幕上
 *
 * @param sprite 要注册的 Sprite
 */
void RegisterSprite(Sprite *sprite);

/**@brief 注册新的 UI Sprite，新的 Sprite 将会被渲染到屏幕上。
 *
 * @param uiSprite 要注册的 Sprite
 */
void RegisterUISprite(Sprite *uiSprite);

/**@brief 暂停游戏，位置更新和碰撞检测将会被暂停，但 UI 并不会受到影响。
 *
 */
void PauseGame();

/**@brief 继续游戏。
 *
 */
void ResumeGame();

/**@brief 获取当前游戏状态，即是否被暂停
 *
 * @return 如果游戏被暂停则返回 true
 */
bool IsPaused();

#endif //PAC_SUPERMAN_ENGINE_H
