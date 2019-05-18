/**@file assets.h
 * @brief 该文件包含了游戏各 Asset 类的定义及相关方法。
 */
#ifndef PAC_SUPERMAN_ASSETS_H
#define PAC_SUPERMAN_ASSETS_H

#include <stdbool.h>
#include <genlib.h>
#include <windef.h>
#include <vector2.h>

typedef struct {
    HBITMAP hbmp;
    HDC mdc;
    int width;
    int height;
} BitmapAsset;

typedef struct {
    unsigned int width;
    unsigned int height;
    BitmapAsset *image;
    short tiles[];
} TiledMapAsset;

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

/**@brief 加载由 Tiled Map Editor 创建的平铺地图。
 *
 * 应提供一个 Tiled Map Editor 创建的 csv 文件及一个可选的 bmp 文件。
 *
 * @param name 地图的名称，即 csv 文件的文件名
 * @param loadImage 是否同时加载图像
 * @return 如果加载成功则返回 TiledMapAsset 对象，否则返回 NULL
 */
TiledMapAsset *LoadTiledMapAsset(string name, bool loadImage);

/**@brief 释放平铺地图资源。
 *
 * @param asset TiledMapAsset 对象
 */
void FreeTiledMapAsset(TiledMapAsset *asset);

#endif //PAC_SUPERMAN_ASSETS_H
