#include <sprite.h>
#include <assets.h>
#include <collider.h>
#include <drawing.h>
#include "map_sprite.h"

static TileCollidersDictAsset *_dict = NULL;

static void _Render(Sprite *this);

static void _Render(Sprite *this) {
    TiledMapAsset *map = this->property;
    DrawBitmapAsset(map->image, this->position, this->size);
//    for (LinkedListNode *node = this->colliders.head; node != NULL; node = node->next) {
//        if (((Collider *) node->element)->type == BOX_COLLIDER)
//            DrawVectorRectangle(
//                    VAdd(this->position, ((Collider *) node->element)->shape.boxCollider.position),
//                    ((Collider *) node->element)->shape.boxCollider.size);
//        else
//            DrawCircle(((Collider *) node->element)->shape.circleCollider.centre.x + this->position.x,
//                       ((Collider *) node->element)->shape.circleCollider.centre.y + this->position.y,
//                       ((Collider *) node->element)->shape.circleCollider.radius);
//    }
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
    if ((double) map->width / map->height > position.x / position.y) {
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