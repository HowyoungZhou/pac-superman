#include <math.h>
#include <sprite.h>
#include <extgraph.h>
#include <drawing.h>
#include <assets.h>
#include "pellet_sprite.h"

static unsigned int _spriteCount = 0;
static BitmapAsset *_asset = NULL;

static void _Render(Sprite *this) {
    DrawBitmapAsset(_asset, this->position, this->size);
}

static void _Collide(Sprite *this, int id, Sprite *other) {
    this->visible = false;
}

static void _Destruct(Sprite *this) {
    _spriteCount--;
    if (_spriteCount == 0 && _asset != NULL) {
        FreeBitmapAsset(_asset);
        _asset = NULL;
    }
    DestructSprite(this);
}

Sprite *ConstructPellet(Vector2 position, Vector2 size) {
    _spriteCount++;
    Sprite *obj = ConstructSprite(position, size, ZERO_VECTOR);
    if (_asset == NULL) _asset = LoadBitmapAsset("pellet.bmp");
    RegisterCircleCollider(obj, DEFAULT_COLLIDER_ID, false, CalcRelativeCentre(obj), CalcIncircleRadius(obj));
    obj->renderer.Render = _Render;
    obj->Collide = _Collide;
    obj->Destruct = _Destruct;
    return obj;
}
