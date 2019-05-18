#include <genlib.h>
#include <rpc.h>
#include <extgraph.h>
#include <linked_list.h>
#include "assets.h"

#ifdef NDEBUG
static string _assetsRoot = "assets/";
#else
static string _assetsRoot = "../assets/";
#endif

static bool _LoadMap(string path, LinkedList *output, unsigned int *height);

string GetAssetsRootPath() {
    return _assetsRoot;
}

void SetAssetsRootPath(string path) {
    _assetsRoot = path;
}

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

static bool _LoadMap(string path, LinkedList *output, unsigned int *height) {
    FILE *fp = fopen(path, "r");
    if (fp == NULL) return false;
    unsigned int h = 0;
    short num = 0, sign = 1;
    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        switch (ch) {
            case '-':
                sign = -1;
                break;
            case '\n':
                h++;
            case ',':;
                short *pnum = malloc(sizeof(short));
                *pnum = sign * num;
                AddElement(output, pnum);
                sign = 1;
                num = 0;
                break;
            default:
                if (isdigit(ch)) {
                    num = num * 10 + ch - '0';
                }
        }
    }
    *height = h;
    if (fclose(fp)) return false;
    return true;
}

TiledMapAsset *LoadTiledMapAsset(string name, bool loadImage) {
    char mapPath[MAX_PATH];
    strcpy(mapPath, _assetsRoot);
    strcat(mapPath, name);
    strcat(mapPath, ".csv");

    unsigned int height;
    LinkedList list = EMPTY_LINKED_LIST;
    if (!_LoadMap(mapPath, &list, &height) || list.length == 0) return NULL;

    TiledMapAsset *obj = malloc(sizeof(TiledMapAsset) + list.length * sizeof(short));
    int i = 0;
    LinkedListNode *node = list.head;
    for (; i < list.length && node != NULL; i++, node = node->next) {
        obj->tiles[i] = *(int *) node->element;
    }
    obj->height = height;
    obj->width = list.length / height;
    ClearList(&list, free);

    if (loadImage) {
        char imagePath[MAX_PATH];
        strcpy(imagePath, _assetsRoot);
        strcat(imagePath, name);
        strcat(imagePath, ".bmp");
        BitmapAsset *image = LoadBitmapAsset(imagePath);
        if (image == NULL)return NULL;
        obj->image = image;
    }

    return obj;
}

void FreeTiledMapAsset(TiledMapAsset *asset) {
    if (asset == NULL) Error("FreeTiledMapAsset: asset can not be NULL.");
    if (asset->image != NULL)FreeBitmapAsset(asset->image);
    free(asset);
}
