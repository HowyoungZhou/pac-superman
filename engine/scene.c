#include <stdlib.h>
#include <string.h>
#include "sprite.h"
#include "scene.h"
#include "engine.h"

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

bool _RemoveGameSprite(Scene *this, Sprite *sprite) {
    if (RemoveElement(&this->gameSprites, sprite, PointerComparer)) {
        sprite->Destruct(sprite);
        return true;
    }
    return false;
}

bool RemoveGameSprite(Scene *this, string name) {
    Sprite *sprite = FindGameSpriteByName(this, name);
    if (!sprite)return false;
    if (GetCurrentScene() == this) {
        RemoveGameSpriteFromCurrentScene(sprite);
        return true;
    } else return _RemoveGameSprite(this, sprite);
}

bool _RemoveUISprite(Scene *this, Sprite *sprite) {
    if (RemoveElement(&this->gameSprites, sprite, PointerComparer)) {
        sprite->Destruct(sprite);
        return true;
    }
    return false;
}

bool RemoveUISprite(Scene *this, string name) {
    Sprite *sprite = FindUISpriteByName(this, name);
    if (!sprite)return false;
    if (GetCurrentScene() == this) {
        RemoveUISpriteFromCurrentScene(sprite);
        return true;
    } else return _RemoveUISprite(this, sprite);
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
