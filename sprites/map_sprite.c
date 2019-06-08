#include <sprite.h>
#include <assets.h>
#include <collider.h>
#include <drawing.h>
#include "map_sprite.h"

static void _Render(Sprite *this);

static void _Destruct(Sprite *this);

static void _Collide(Sprite *this, int id, Sprite *other);

static void _RegisterColliders(Sprite *this);

static TileCollidersDictAsset *_dict = NULL;

static void _Render(Sprite *this) {
    TiledMapAsset *map = this->property;
    DrawBitmapAsset(map->image, this->position, this->size);
}

static void _Destruct(Sprite *this) {
    FreeTiledMapAsset(this->property);
    DestructSprite(this);
}

static void _Collide(Sprite *this, int id, Sprite *other) {
    other->velocity = ZERO_VECTOR;
}

static void _RegisterColliders(Sprite *this) {
    int count = 0;
    TiledMapAsset *map = this->property;
    const Vector2 tileSize = GetTileSize(this);
    for (unsigned int i = 0; i < map->width; i++) {
        for (unsigned int j = 0; j < map->height; j++, count++) {
            int n;
            Collider *colliders = FindCollidersInDict(_dict, GetTileAt(map, i, j), &n);
            for (int k = 0; k < n; k++) {
                Vector2 tilePos = GetRelativeTilePosition(this, i, j);
                switch (colliders[k].type) {
                    case BOX_COLLIDER:;
                        BoxCollider boxCollider = colliders[k].shape.boxCollider;
                        RegisterBoxCollider(this, count, true,
                                            V2DScale(boxCollider.size, tileSize),
                                            VAdd(tilePos, V2DScale(boxCollider.position, tileSize)));
                        break;
                    case CIRCLE_COLLIDER:;
                        CircleCollider circleCollider = colliders[k].shape.circleCollider;
                        RegisterCircleCollider(this, count, true,
                                               VAdd(tilePos, V2DScale(circleCollider.centre, tileSize)),
                                               circleCollider.radius * tileSize.x);
                        break;
                }
            }
        }
    }
}

Sprite *ConstructMapSprite(string mapName, string collidersDictFile, Vector2 position, Vector2 size) {
    TiledMapAsset *map = LoadTiledMapAsset(mapName, true, true);
    if (map == NULL)return NULL;
    Sprite *obj;
    if ((double) map->width / map->height > size.x / size.y) {
        double height = size.x * map->height / map->width;
        obj = ConstructSprite((Vector2) {position.x, position.y + (size.y - height) / 2.},
                              (Vector2) {size.x, height},
                              ZERO_VECTOR);
    } else {
        double width = size.y * map->width / map->height;
        obj = ConstructSprite((Vector2) {position.x + (size.x - width) / 2., position.y},
                              (Vector2) {width, size.y},
                              ZERO_VECTOR);
    }
    obj->name = "Map";
    obj->renderer.Render = _Render;
    obj->property = map;
    obj->Destruct = _Destruct;
    obj->Collide = _Collide;
    if (_dict == NULL) _dict = LoadTileCollidersDictAsset(collidersDictFile);
    _RegisterColliders(obj);
    return obj;
}

Vector2 GetTileSize(Sprite *this) {
    TiledMapAsset *map = this->property;
    return (Vector2) {this->size.x / map->width, this->size.y / map->height};
}

Vector2 GetRelativeTilePosition(Sprite *this, unsigned int x, unsigned int y) {
    TiledMapAsset *map = this->property;
    return (Vector2) {this->size.x * x / map->width, this->size.y * y / map->height};
}

Vector2 GetTilePosition(Sprite *this, unsigned int x, unsigned int y) {
    return VAdd(this->position, GetRelativeTilePosition(this, x, y));
}

bool IsTileWalkable(Sprite *this, unsigned int x, unsigned int y) {
    short tile = GetTileAt(this->property, x, y);
    for (int i = 0; i < _dict->length; i++) {
        if (tile == _dict->colliders[i].id) return false;
    }
    return true;
}

TileCoordinate FindTileCoordinate(Sprite *this, Vector2 position) {
    TiledMapAsset *map = this->property;
    Vector2 relativePos = VSubtract(position, this->position);
    Vector2 tileSize = GetTileSize(this);
    int x = relativePos.x / tileSize.x;
    int y = relativePos.y / tileSize.y;
    x = x < 0 ? 0 : x;
    y = y < 0 ? 0 : y;
    x = x > map->width - 1 ? map->width - 1 : x;
    y = y > map->height - 1 ? map->height - 1 : y;
    return (TileCoordinate) {x, y};
}

bool FindGameObjectOfMap(Sprite *this, string name, GameObject *output) {
    TiledMapAsset *map = this->property;
    GameObject obj;
    if (!FindGameObject(map->gameObjects, name, &obj))return false;
    obj.position.y = map->image->height - obj.position.y - obj.size.y; // 将坐标转换为以左下角为坐标系
    // 将大小和位置按照实际 Sprite 大小缩放
    obj.size = V2DScale(obj.size, (Vector2) {this->size.x / map->image->width, this->size.y / map->image->height});
    obj.position = VAdd(this->position, V2DScale(obj.position, (Vector2) {this->size.x / map->image->width,
                                                                          this->size.y / map->image->height}));
    *output = obj;
    return true;
}

void ForEachTile(Sprite *this, ForEachTileCallback callback) {
    TiledMapAsset *map = this->property;
    for (unsigned int i = 0; i < map->width; i++) {
        for (unsigned int j = 0; j < map->height; j++) {
            callback(this, i, j, GetTileAt(map, i, j));
        }
    }
}

TiledMapAsset *GetMapAsset(Sprite *this) {
    return this->property;
}
