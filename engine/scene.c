#include <stdlib.h>
#include <string.h>
#include "sprite.h"
#include "scene.h"

static void _DestructSprite(void *sprite);

static bool _SpriteNameIdentifier(void *element, void *param) {
    return strcmp(((Sprite *) element)->name, param) == 0;
}

static void _DestructSprite(void *sprite) {
    ((Sprite *) sprite)->Destruct(sprite);
}

void AddGameSprite(Scene *this, Sprite *sprite) {
    AddElement(&this->gameSprites, sprite);
}

void AddUISprite(Scene *this, Sprite *uiSprite) {
    AddElement(&this->uiSprites, uiSprite);
}

Sprite *FindGameSpriteByName(Scene *this, string name) {
    return SearchElement(&this->gameSprites, name, _SpriteNameIdentifier);
}

Sprite *FindUISpriteByName(Scene *this, string name) {
    return SearchElement(&this->uiSprites, name, _SpriteNameIdentifier);
}

void ClearGameSprites(Scene *this) {
    ClearList(&this->gameSprites, _DestructSprite);
}

void ClearUISprites(Scene *this) {
    ClearList(&this->uiSprites, _DestructSprite);
}

void DestructScene(Scene *this) {
    ClearList(&this->gameSprites, _DestructSprite);
    ClearList(&this->uiSprites, _DestructSprite);
    free(this);
}

Scene *ConstructScene(Initializer initializer) {
    Scene *obj = malloc(sizeof(Scene));
    obj->uiSprites = EMPTY_LINKED_LIST;
    obj->gameSprites = EMPTY_LINKED_LIST;
    obj->backColor = "Black";
    obj->Initialize = initializer;
    obj->Destruct = DestructScene;
    return obj;
}
