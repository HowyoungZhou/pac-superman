#include <sprite.h>
#include <assets.h>
#include "map_sprite.h"

static void _Render(Sprite *this);

static void _Render(Sprite *this) {
    TiledMapAsset *map = this->property;
    DrawBitmapAsset(map->image, this->position, this->size);
}

static void _Destruct(Sprite *this) {
    FreeTiledMapAsset(this->property);
    DestructSprite(this);
}

Sprite *ConstructMapSprite(string mapName, Vector2 position, Vector2 size) {
    TiledMapAsset *map = LoadTiledMapAsset(mapName, true);
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
}
