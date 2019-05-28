#include <assets.h>
#include <sprite.h>

static unsigned int _spriteCount = 0;
static BitmapAsset *_asset = NULL;

static void _Animate(Animator *this, Sprite *sprite, Frame frame) {
    if (frame == 0)DrawBitmapAsset(_asset, sprite->position, sprite->size);
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

Sprite *ConstructPowerPellet(Vector2 position, Vector2 size) {
    _spriteCount++;
    Sprite *obj = ConstructSprite(position, size, ZERO_VECTOR);
    if (_asset == NULL) _asset = LoadBitmapAsset("pellet.bmp");
    RegisterCircleCollider(obj, DEFAULT_COLLIDER_ID, false, CalcRelativeCentre(obj), CalcIncircleRadius(obj));

    Animator *animator = ConstructAnimator(2);
    animator->Animate = _Animate;
    for (int i = 0; i < 2; i++)animator->intervals[i] = 200;

    obj->hasAnimation = true;
    obj->renderer.animator = animator;
    obj->Collide = _Collide;
    obj->Destruct = _Destruct;
    return obj;
}
