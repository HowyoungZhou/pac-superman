#ifndef PAC_SUPERMAN_MAP_SPRITE_H
#define PAC_SUPERMAN_MAP_SPRITE_H

#include <assets.h>

Sprite *ConstructMapSprite(string mapName, string collidersDictFile, Vector2 position, Vector2 size);

Vector2 GetTileSize(Sprite *this);

Vector2 GetRelativeTilePosition(Sprite *this, unsigned int x, unsigned int y);

bool FindGameObjectOfMap(Sprite *this, string name, GameObject *output);

#endif //PAC_SUPERMAN_MAP_SPRITE_H
