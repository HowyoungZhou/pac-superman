#include <stdlib.h>
#include <genlib.h>
#include "graphics.h"
#include "vector2.h"
#include "sprite.h"
#include "drawing.h"

void RenderExampleSprite(Sprite *this) {
    DrawVectorRectangle(this->position, this->size, TRUE);
}

Sprite *ConstructExampleSprite() {
    Sprite *obj = ConstructSprite((Vector2) {0, 0}, (Vector2) {0.2, 0.2}, (Vector2) {0.001, 0.001});
    obj->renderer.Render = RenderExampleSprite;
    return obj;
}
