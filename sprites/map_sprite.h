#ifndef PAC_SUPERMAN_MAP_SPRITE_H
#define PAC_SUPERMAN_MAP_SPRITE_H

#include <assets.h>

typedef void (*ForEachTileCallback)(Sprite *sprite, unsigned int x, unsigned int y, short id);

Sprite *ConstructMapSprite(string mapName, string collidersDictFile, Vector2 position, Vector2 size);

Vector2 GetTileSize(Sprite *this);

Vector2 GetRelativeTilePosition(Sprite *this, unsigned int x, unsigned int y);

Vector2 GetTilePosition(Sprite *this, unsigned int x, unsigned int y);

bool FindGameObjectOfMap(Sprite *this, string name, GameObject *output);

void ForEachTile(Sprite *this, ForEachTileCallback callback);

TiledMapAsset *GetMapAsset(Sprite *this);

#endif //PAC_SUPERMAN_MAP_SPRITE_H