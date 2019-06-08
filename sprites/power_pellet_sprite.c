#include <assets.h>
#include <sprite.h>
#include <game_controller.h>
#include <game_scene.h>

#define POWER_PELLET_SCORE 100

static unsigned int _spriteCount = 0;
static BitmapAsset *_asset = NULL;

static void _Animate(Animator *this, Sprite *sprite, Frame frame) {
    if (frame == 0)DrawBitmapAsset(_asset, sprite->position, sprite->size);
}

static void _Collide(Sprite *this, int id, Sprite *other) {
    if (other->name && !strcmp(other->name, "PacMan")) {
        this->visible = false;
        PowerModeOn();
        ChangeScore(POWER_PELLET_SCORE);
        ChangeRemainingPellets(-1);
        if (GetRemainingPellets() == 0) EndGame(WIN);
    }
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

    obj->name = "PowerPellet";
    obj->hasAnimation = true;
    obj->renderer.animator = animator;
    obj->Collide = _Collide;
    obj->Destruct = _Destruct;
    return obj;
}
