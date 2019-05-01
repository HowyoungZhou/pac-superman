#include <math.h>
#include <sprite.h>
#include <extgraph.h>
#include <drawing.h>
#include "pellet.h"

static void _Render(Sprite *this) {
    SetPenColor("Pellet");
    StartFilledRegion(1.);
    DrawVectorCircle(CalcCentre(this), CalcIncircleRadius(this));
    EndFilledRegion();
}

static void _Collide(Sprite *this, int id, Sprite *other) {
    this->visible = false;
}

Sprite *ConstructPellet(Vector2 position, Vector2 size) {
    Sprite *obj = ConstructSprite(position, size, ZERO_VECTOR);
    obj->renderer.Render = _Render;
    RegisterCircleCollider(obj, DEFAULT_COLLIDER_ID, false, CalcRelativeCentre(obj), CalcIncircleRadius(obj));
    obj->Collide = _Collide;
    return obj;
}
