/**@file scene.h
 * @brief 该文件包含了 Scene 类的定义及相关方法。
 */
#ifndef PAC_SUPERMAN_SCENE_H
#define PAC_SUPERMAN_SCENE_H

#include <sprite.h>
#include <linked_list.h>
#include <genlib.h>

typedef LinkedList SpritesList;
typedef LinkedListNode SpritesListNode;

struct Scene;

typedef void (*Initializer)(struct Scene *this);

typedef struct Scene {
    SpritesList gameSprites;
    SpritesList uiSprites;
    string backColor;

    Initializer Initialize;

    void (*Destruct)(struct Scene *this);
} Scene;

/**@brief 添加新的游戏 Sprite 到场景中。
 *
 * @param this 目标场景
 * @param sprite 要添加的游戏 Sprite
 */
void AddGameSprite(Scene *this, Sprite *sprite);

/**@brief 添加新的 UI Sprite 到场景中。
 *
 * @param this 目标场景
 * @param uiSprite 要添加的 UI Sprite
 */
void AddUISprite(Scene *this, Sprite *uiSprite);

/**@brief 查找指定名称的游戏 Sprite。
 *
 * @param this 要查找的场景
 * @param name Sprite 名称
 * @return 如找到则返回 Sprite 对象，否则返回 NULL
 */
Sprite *FindGameSpriteByName(Scene *this, string name);

/**@brief 查找指定名称的 UI Sprite。
 *
 * @param this 要查找的场景
 * @param name Sprite 名称
 * @return 如找到则返回 Sprite 对象，否则返回 NULL
 */
Sprite *FindUISpriteByName(Scene *this, string name);

bool _RemoveGameSprite(Scene *this, Sprite *sprite);

bool _RemoveUISprite(Scene *this, Sprite *sprite);

bool RemoveGameSprite(Scene *this, string name);

bool RemoveUISprite(Scene *this, string name);

/**@brief 清除所有 Sprite。
 *
 * 注意：该方法不能在 Render, Animate 或 Update 方法中调用，因为该方法会破坏正常的物理引擎计算和渲染流程。
 */
void ClearGameSprites(Scene *this);

/**@brief 清除所有 Sprite。
 *
 * 注意：该方法不能在 Render, Animate 或 Update 方法中调用，因为该方法会破坏正常的物理引擎计算和渲染流程。
 */
void ClearUISprites(Scene *this);

/**@brief Scene 类的默认析构函数。
 *
 * @param this Scene 对象
 */
void DestructScene(Scene *this);

/**@brief Scene 类的构造函数。
 *
 * @param initializer 场景的初始化器，该函数在加载场景时会被调用
 * @return 构造的 Scene 对象
 */
Scene *ConstructScene(Initializer initializer);

#endif //PAC_SUPERMAN_SCENE_H
