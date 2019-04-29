#include <stdlib.h>
#include <genlib.h>
#include "extgraph.h"
#include "graphics.h"
#include "sprite.h"
#include "vector2.h"
#include "drawing.h"

static void _RenderExampleSprite(Sprite *this);

static void _RenderExampleSprite(Sprite *this) {
    StartFilledRegion(0);
    DrawVectorRectangle(this->position, this->size);
    EndFilledRegion();
}

Sprite *ConstructExampleSprite() {
    Sprite *obj = ConstructSprite((Vector2) {0, 0.5}, (Vector2) {0.5, 0.5}, (Vector2) {1, 0});
    obj->renderer.Render = _RenderExampleSprite;
    return obj;
}
