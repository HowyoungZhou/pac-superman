#include "pause_button.h"
#include <stdlib.h>
#include <sprite.h>
#include <engine.h>
#include "imgui.h"

static void _Render(Sprite *this);

static void _Render(Sprite *this) {
    string label = IsPaused() ? "Resume" : "Pause";
    if (button(GenUIID(0), this->position.x, this->position.y, this->size.x, this->size.y, label)) {
        if (IsPaused()) ResumeGame();
        else PauseGame();
    }
}

Sprite *ConstructPauseButtonSprite(Vector2 position, Vector2 size) {
    Sprite *obj = ConstructSprite(position, size, ZERO_VECTOR);
    obj->renderer.Render = _Render;
    return obj;
}