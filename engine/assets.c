#include <genlib.h>
#include <rpc.h>
#include <extgraph.h>
#include <linked_list.h>
#include "assets.h"
#include "collider.h"

#ifdef NDEBUG
static string _assetsRoot = "assets/";
#else
static string _assetsRoot = "../assets/";
#endif

static bool _ReadObjFile(string path, LinkedList *output);

static bool _LoadMap(string path, LinkedList *output, unsigned int *height);

static bool _ReadDictFile(string path, LinkedList *output);

static void _DestructCollider(void *collider);

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

static bool _ReadObjFile(string path, LinkedList *output) {
    FILE *fp = fopen(path, "r");
    if (fp == NULL) return false;
    char line[MAX_LINE_LENGTH];

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        GameObject *object = malloc(sizeof(GameObject));
        if (sscanf(line, "%s %lf %lf %lf %lf", object->name, &object->position.x, &object->position.y, &object->size.x,
                   &object->size.y) != 5)
            return false;
        AddElement(output, object);
    }
    if (fclose(fp)) return false;
    return true;
}

GameObjectsListAsset *LoadGameObjectsListAsset(string file) {
    char objPath[MAX_PATH];
    strcpy(objPath, _assetsRoot);
    strcat(objPath, file);

    LinkedList list = EMPTY_LINKED_LIST;
    if (!_ReadObjFile(objPath, &list)) {
        ClearList(&list, free);
        return NULL;
    }

    GameObjectsListAsset *asset = malloc(sizeof(GameObjectsListAsset) + list.length * sizeof(GameObject));
    asset->length = list.length;
    LinkedListNode *node = list.head;
    int i = 0;
    for (; node != NULL && i < list.length; node = node->next, i++) {
        asset->gameObjects[i] = *(GameObject *) node->element;
    }
    ClearList(&list, _DestructCollider);

    return asset;
}

void FreeGameObjectsListAsset(GameObjectsListAsset *asset) {
    free(asset);
}

bool FindGameObject(GameObjectsListAsset *asset, string name, GameObject *output) {
    for (int i = 0; i < asset->length; i++) {
        if (strcmp(asset->gameObjects[i].name, name) != 0)continue;
        *output = asset->gameObjects[i];
        return true;
    }
    return false;
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

TiledMapAsset *LoadTiledMapAsset(string file, bool loadImage, bool loadObjects) {
    char mapPath[MAX_PATH];
    strcpy(mapPath, _assetsRoot);
    strcat(mapPath, file);
    strcat(mapPath, ".csv");

    unsigned int height;
    LinkedList list = EMPTY_LINKED_LIST;
    if (!_LoadMap(mapPath, &list, &height) || list.length == 0) {
        ClearList(&list, free);
        return NULL;
    }

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
        strcpy(imagePath, file);
        strcat(imagePath, ".bmp");
        BitmapAsset *image = LoadBitmapAsset(imagePath);
        if (image == NULL)return NULL;
        obj->image = image;
    }

    if (loadObjects) {
        char objPath[MAX_PATH];
        strcpy(objPath, file);
        strcat(objPath, ".gobj");
        GameObjectsListAsset *objects = LoadGameObjectsListAsset(objPath);
        if (objects == NULL)return NULL;
        obj->gameObjects = objects;
    }

    return obj;
}

void FreeTiledMapAsset(TiledMapAsset *asset) {
    if (asset == NULL) Error("FreeTiledMapAsset: asset can not be NULL.");
    if (asset->image != NULL)FreeBitmapAsset(asset->image);
    free(asset);
}

short GetTileAt(TiledMapAsset *asset, unsigned int x, unsigned int y) {
    return asset->tiles[(asset->height - 1 - y) * asset->width + x];
}

static bool _ReadDictFile(string path, LinkedList *output) {
    FILE *fp = fopen(path, "r");
    if (fp == NULL) return false;
    char line[MAX_LINE_LENGTH];

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        int id, pos = 0, dpos;
        char type;
        if (sscanf(line + pos, "%d%n", &id, &dpos) != 1) return false;
        pos += dpos;
        while (sscanf(line + pos, " %c%n", &type, &dpos) == 1) {
            pos += dpos;
            switch (type) {
                case 'B':;
                    double x, y, width, height;
                    if (sscanf(line + pos, "%lf %lf %lf %lf%n", &x, &y, &width, &height, &dpos) != 4)return false;
                    pos += dpos;
                    Collider *bCollider = ConstructCollider(id, BOX_COLLIDER, true);
                    bCollider->shape.boxCollider = (BoxCollider) {(Vector2) {width, height}, (Vector2) {x, y}};
                    AddElement(output, bCollider);
                    break;
                case 'C':;
                    double cx, cy, radius;
                    if (sscanf(line + pos, "%lf %lf %lf%n", &cx, &cy, &radius, &dpos) != 3)return false;
                    pos += dpos;
                    Collider *cCollider = ConstructCollider(id, CIRCLE_COLLIDER, true);
                    cCollider->shape.circleCollider = (CircleCollider) {(Vector2) {cx, cy}, radius};
                    AddElement(output, cCollider);
                    break;
                default:
                    return false;
            }
        }
    }
    if (fclose(fp)) return false;
    return true;
}

static void _DestructCollider(void *collider) {
    DestructCollider(collider);
}

TileCollidersDictAsset *LoadTileCollidersDictAsset(string file) {
    char dictPath[MAX_PATH];
    strcpy(dictPath, _assetsRoot);
    strcat(dictPath, file);

    LinkedList list = EMPTY_LINKED_LIST;
    if (!_ReadDictFile(dictPath, &list)) {
        ClearList(&list, _DestructCollider);
        return NULL;
    }

    TileCollidersDictAsset *asset = malloc(sizeof(TileCollidersDictAsset) + list.length * sizeof(Collider));
    asset->length = list.length;
    LinkedListNode *node = list.head;
    int i = 0;
    for (; node != NULL && i < list.length; node = node->next, i++) {
        asset->colliders[i] = *(Collider *) node->element;
    }
    ClearList(&list, _DestructCollider);

    return asset;
}

void FreeTileCollidersDictAsset(TileCollidersDictAsset *asset) {
    if (asset == NULL) Error("TileCollidersDictAsset: asset can not be NULL.");
    free(asset);
}

Collider *FindCollidersInDict(TileCollidersDictAsset *dict, short id, int *lengthOutput) {
    int length = 0;
    Collider *res = NULL;
    for (int i = 0; i < dict->length; i++) {
        if (dict->colliders[i].id == id) {
            if (res == NULL) res = dict->colliders + i;
            length++;
        } else if (res != NULL) break;
    }
    *lengthOutput = length;
    return res;
}