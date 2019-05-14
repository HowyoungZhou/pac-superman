#include <genlib.h>
#include <rpc.h>
#include <extgraph.h>
#include "assets.h"

#ifdef NDEBUG
static string _assetsRoot = "assets/";
#else
static string _assetsRoot = "../assets/";
#endif

BitmapAsset *LoadBitmapAsset(string file) {
    char path[MAX_PATH];
    strcpy(path, _assetsRoot);
    strcat(path, file);
    // 加载图像
    HBITMAP hbmp = LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (hbmp == NULL)return NULL;
    // 创建 Memory DC
    HDC mdc = CreateCompatibleDC(NULL);
    if (mdc == NULL) {
        DeleteObject(hbmp);
        return NULL;
    }
    // 获取图像大小
    BITMAP bmp;
    if (GetObject(hbmp, sizeof(bmp), &bmp) == 0) {
        DeleteObject(hbmp);
        DeleteDC(mdc);
        return NULL;
    }
    // 将位图写入 Memory DC
    HGDIOBJ obj = SelectObject(mdc, hbmp);
    if (obj == NULL || obj == HGDI_ERROR) {
        DeleteObject(hbmp);
        DeleteDC(mdc);
        return NULL;
    }
    BitmapAsset *asset = malloc(sizeof(BitmapAsset));
    asset->width = bmp.bmWidth;
    asset->height = bmp.bmHeight;
    asset->hbmp = hbmp;
    asset->mdc = mdc;
    return asset;
}

void DrawBitmapAsset(BitmapAsset *asset, Vector2 position, Vector2 size) {
    if (asset == NULL) Error("DrawBitmapAsset: asset can not be NULL.");
    DrawBitmap(asset->mdc, position.x, position.y, size.x, size.y, asset->width, asset->height);
}

void FreeBitmapAsset(BitmapAsset *asset) {
    if (asset == NULL) Error("FreeBitmapAsset: asset can not be NULL.");
    DeleteObject(asset->hbmp);
    DeleteDC(asset->mdc);
    free(asset);
}

string GetAssetsRootPath() {
    return _assetsRoot;
}

void SetAssetsRootPath(string path) {
    _assetsRoot = path;
}
