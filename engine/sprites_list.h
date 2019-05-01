#ifndef PAC_SUPERMAN_SPRITES_LIST_H
#define PAC_SUPERMAN_SPRITES_LIST_H

#include <stdlib.h>
#include "sprite.h"

typedef void (*ForEachSpriteCallback)(Sprite *sprite);

typedef struct spritesListNode {
    Sprite *sprite;
    struct spritesListNode *next;
} SpritesListNode;

typedef struct spritesList {
    struct spritesListNode *head;
    struct spritesListNode *tail;
    unsigned int length;
} SpritesList;

void RegisterSprite(Sprite *sprite);

void ForEachSprite(ForEachSpriteCallback callback);

SpritesListNode *GetSpritesListHead();

#endif //PAC_SUPERMAN_SPRITES_LIST_H
