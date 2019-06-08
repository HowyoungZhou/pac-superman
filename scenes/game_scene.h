#ifndef PAC_SUPERMAN_TEST_SCENE_H
#define PAC_SUPERMAN_TEST_SCENE_H

#include <dynamic_array.h>

typedef struct {
    Sprite *map;
    Sprite *pacman;
    Sprite *blinky;
    Sprite *pinky;
    Sprite *inky;
    Sprite *clyde;
} Heroes;

/**@brief GameScene 的构造函数。
 *
 * @return GameScene 对象
 */
Scene *ConstructGameScene(string mapName);

/**@brief 获取平铺地图上所有可以到达的位置。
 *
 * @return 存储了平铺地图上所有可以到达的位置的动态数组。
 */
DynamicArray GetAllWalkableTiles();

/**@brief 复活吃豆人。
 *
 */
void RevivePacMan();

/**@brief 吃豆人吃下大力丸后进入“大力”模式。
 *
 */
void PowerModeOn();

/**@brief 启动新游戏。
 *
 * 即在当前地图下重置游戏状态。
 *
 */
void NewGame();

/**@brief 获取当前游戏中的实体对象。
 *
 * @return 当前游戏中的实体对象
 */
Heroes * GetCurrentHeroes();

#endif //PAC_SUPERMAN_TEST_SCENE_H
