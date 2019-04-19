#include "graphics.h"
#include "vector2.h"
#include "sprite.h"

void RenderExampleSprite(Sprite *this) {
    MovePen(this->position.x, this->position.y);
    DrawLine(0, this->size.y);
    DrawLine(this->size.x, 0);
    DrawLine(0, -this->size.y);
    DrawLine(-this->size.x, 0);
}

Sprite *ConstructExampleSprite() {
    Sprite *obj = ConstructSprite(ZERO_VECTOR, (Vector2) {0.2, 0.2}, (Vector2) {0.1, 0});
    //obj->renderer.Render = RenderExampleSprite;
}
