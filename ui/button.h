#ifndef PAC_SUPERMAN_BUTTON_H
#define PAC_SUPERMAN_BUTTON_H

typedef void (*OnClickCallback)(Sprite *button);

typedef struct {
    int id;
    char *label;
    OnClickCallback OnClick;
} Button;

Sprite *ConstructButtonSprite(int id, Vector2 position, Vector2 size, char *label, OnClickCallback onClick);

#endif //PAC_SUPERMAN_BUTTON_H
