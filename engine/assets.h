/**@file assets.h
 * @brief 该文件包含了游戏各 Asset 类的定义及相关方法。
 */
#ifndef PAC_SUPERMAN_ASSETS_H
#define PAC_SUPERMAN_ASSETS_H

#include <stdbool.h>
#include <genlib.h>
#include <windef.h>
#include <vector2.h>
#include "collider.h"

#define MAX_LINE_LENGTH 1000

typedef struct {
    char name[100];
    Vector2 position;
    Vector2 size;
} GameObject;

typedef struct {
    unsigned int length;
    GameObject gameObjects[];
} GameObjectsListAsset;

typedef struct {
    HBITMAP hbmp;
    HDC mdc;
    int width;
    int height;
} BitmapAsset;

typedef struct {
    unsigned int width;
    unsigned int height;
    GameObjectsListAsset *gameObjects;
    BitmapAsset *image;
    short tiles[];
} TiledMapAsset;

typedef struct {
    unsigned int length;
    Collider colliders[];
} TileCollidersDictAsset;

/**@brief 获取资源文件夹根目录。
 *
 * @return 资源文件夹根目录
 */
string GetAssetsRootPath();

/**@brief 修改资源文件夹根目录。
 *
 * 这不会影响已加载的 Asset。
 *
 * @param path 资源文件夹根目录
 */
void SetAssetsRootPath(string path);

/**@brief 从文件中加载位图资源。
 *
 * @param file 位图的路径
 * @return 如果加载成功则返回 BitmapAsset 对象，否则返回 NULL
 */
BitmapAsset *LoadBitmapAsset(string file);

/**@brief 在指定位置以指定大小绘制位图。
 *
 * 如果指定大小与位图原大小不相符，那么图像会被拉伸。
 *
 * @param asset BitmapAsset 对象
 * @param position 绘制位图的位置
 * @param size 绘制位图的大小
 */
void DrawBitmapAsset(BitmapAsset *asset, Vector2 position, Vector2 size);

/**@brief 释放位图资源。
 *
 * @param asset BitmapAsset 对象
 */
void FreeBitmapAsset(BitmapAsset *asset);

/**@brief 加载游戏实体列表资源。
 *
 * @param file 资源文件
 * @return 如果加载成功则返回 GameObjectsListAsset 对象，否则返回 NULL
 */
GameObjectsListAsset *LoadGameObjectsListAsset(string file);

/**@brief 释放游戏实体列表资源。
 *
 * @param asset GameObjectsListAsset 对象
 */
void FreeGameObjectsListAsset(GameObjectsListAsset *asset);

/**@brief 从游戏实体列表中查找某实体。
 *
 * @param asset 游戏实体列表资源
 * @param name 实体名称
 * @param output 用于储存查找到的游戏实体的变量地址
 * @return 如查找成功则返回 true，否则返回 false。
 */
bool FindGameObject(GameObjectsListAsset *asset, string name, GameObject *output);

/**@brief 加载由 Tiled Map Editor 创建的平铺地图。
 *
 * 应提供一个 Tiled Map Editor 创建的 csv 文件及一个可选的 bmp 文件。
 *
 * @param file 地图的名称，即 csv 文件的文件名
 * @param loadImage 是否同时加载图像
 * @param loadObjects 是否同时加载游戏实体列表
 * @return 如果加载成功则返回 TiledMapAsset 对象，否则返回 NULL
 */
TiledMapAsset *LoadTiledMapAsset(string file, bool loadImage, bool loadObjects);

/**@brief 释放平铺地图资源。
 *
 * @param asset TiledMapAsset 对象
 */
void FreeTiledMapAsset(TiledMapAsset *asset);

/**@brief 获取平铺地图某一位置上的 Tile ID。
 *
 * 坐标以左下角为原点。
 *
 * @param asset TiledMapAsset 对象
 * @param x x 坐标
 * @param y y 坐标
 * @return (x, y) 位置上的 Tile ID
 */
short GetTileAt(TiledMapAsset *asset, unsigned int x, unsigned int y);

/**@brief 加载平铺地图碰撞器配置资源。
 *
 * @param file 资源文件
 * @return 如果加载成功则返回 TileCollidersDictAsset 对象，否则返回 NULL
 */
TileCollidersDictAsset *LoadTileCollidersDictAsset(string file);

/**@brief 释放平铺地图碰撞器配置资源。
 *
 * @param asset TileCollidersDictAsset 对象
 */
void FreeTileCollidersDictAsset(TileCollidersDictAsset *asset);

/**@brief 获取平铺地图碰撞器配置 (TileCollidersDict) 中某图块 ID 对应的碰撞器。
 *
 * @param dict TileCollidersDictAsset 对象
 * @param id 图块 ID
 * @param lengthOutput 用于输出查找到的碰撞器个数的变量地址
 * @return 查找到的 Collider 数组
 */
Collider *FindCollidersInDict(TileCollidersDictAsset *dict, short id, int *lengthOutput);

#endif //PAC_SUPERMAN_ASSETS_H
