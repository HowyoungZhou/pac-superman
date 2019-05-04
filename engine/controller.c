#include <vector2.h>
#include <events.h>
#include "controller.h"

static void _ControllerCallback(int key, int event);

enum DirectionKeys {
    LEFT = 37,
    UP = 38,
    RIGHT = 39,
    DOWN = 40,
    W = 87,
    A = 65,
    S = 83,
    D = 68
};

static Vector2 _controllerVector = ZERO_VECTOR;

void InitController() {
    RegisterKeyboardEvent(_ControllerCallback);
}

Vector2 GetControllerVector() {
    return _controllerVector;
}

Vector2 GetNormalizedControllerVector() {
    return VNormalize(_controllerVector);
}

static void _ControllerCallback(int key, int event) {
    switch (key) {
        case UP:
        case W:
            _controllerVector.y = event == KEY_DOWN ? 1 : 0;
            break;
        case DOWN:
        case S:
            _controllerVector.y = event == KEY_DOWN ? -1 : 0;
            break;
        case LEFT:
        case A:
            _controllerVector.x = event == KEY_DOWN ? -1 : 0;
            break;
        case RIGHT:
        case D:
            _controllerVector.x = event == KEY_DOWN ? 1 : 0;
            break;
        default:
            break;
    }
}