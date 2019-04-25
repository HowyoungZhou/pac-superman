#include <stdlib.h>
#include "sprites_list.h"

static SpritesList _spritesList = {NULL, NULL, 0};

void RegisterSprite(Sprite *sprite) {
    SpritesListNode *node = malloc(sizeof(SpritesListNode));
    node->sprite = sprite;
    node->next = NULL;
    if (_spritesList.head == NULL) {
        _spritesList.head = _spritesList.tail = node;
    } else {
        _spritesList.tail->next = node;
        _spritesList.tail = node;
    }
    _spritesList.length++;
}

void ForEachSprite(ForEachSpriteCallback callback) {
    for (SpritesListNode *node = _spritesList.head; node != NULL; node = node->next) {
        callback(node->sprite);
    }
}

SpritesList GetSpritesList() {
    return _spritesList;
}
