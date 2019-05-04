#include <stdlib.h>
#include <sprite.h>
#include "button.h"
#include "imgui.h"

static inline Button *_ConstructButton(int id, char *label, OnClickCallback onClick);

static void _Destruct(Sprite *this);

static void _Render(Sprite *this);

static inline Button *_ConstructButton(int id, char *label, OnClickCallback onClick) {
    Button *obj = malloc(sizeof(Button));
    obj->id = id;
    obj->label = label;
    obj->OnClick = onClick;
    return obj;
}

static void _Destruct(Sprite *this) {
    free(this->property);
    DestructSprite(this);
}

static void _Render(Sprite *this) {
    Button *buttonObj = this->property;
    int res = button(buttonObj->id, this->position.x, this->position.y, this->size.x, this->size.y, buttonObj->label);
    if (!res)return;
    if (buttonObj->OnClick != NULL)buttonObj->OnClick(this);
}

Sprite *ConstructButtonSprite(int id, Vector2 position, Vector2 size, char *label, OnClickCallback onClick) {
    Sprite *obj = ConstructSprite(position, size, ZERO_VECTOR);
    obj->property = _ConstructButton(id, label, onClick);
    obj->Destruct = _Destruct;
    obj->renderer.Render = _Render;
    return obj;
}