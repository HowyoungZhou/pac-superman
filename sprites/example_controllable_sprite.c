#include <vector2.h>
#include <sprite.h>
#include <extgraph.h>
#include <drawing.h>
#include <controller.h>
#include "example_controllable_sprite.h"

#define SPEED 0.001

static void _RenderExampleControllableSprite(Sprite *this, double interval);

static void _RenderExampleControllableSprite(Sprite *this, double interval) {
    StartFilledRegion(.5);
    DrawVectorRectangle(this->position, this->size);
    EndFilledRegion();
    // 通过 Controller 更新速度
    this->velocity = VMultiply(SPEED, GetNormalizedControllerVector());
}

Sprite *ConstructExampleControllableSprite() {
    // 创建一个 Sprite
    Sprite *obj = ConstructSprite((Vector2) {0, 0.5}, (Vector2) {0.5, 0.5}, ZERO_VECTOR);
    obj->renderer.Render = _RenderExampleControllableSprite;
    return obj;
}