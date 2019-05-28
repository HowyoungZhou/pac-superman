#include <sprite.h>
#include <graphics.h>
#include <drawing.h>
#include "walls.h"

static int map1[23][23] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1},
        {1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void Draw1_1(double d, double x, double y) {
    MovePen(x, y - d / 3.0);
    DrawLine(d / 2.0, 0);
    DrawArc(d / 6.0, 90, -180);
    DrawLine(-d / 2.0, 0);
    MovePen(x, y);
}

void Draw1_2(double d, double x, double y) {
    MovePen(x + 2 * d / 3.0, y);
    DrawLine(0, -d / 2.0);
    DrawArc(d / 6.0, 0, -180);
    DrawLine(0, d / 2.0);
    MovePen(x, y);
}

void Draw1_3(double d, double x, double y) {
    MovePen(x + d, y - 2 * d / 3.0);
    DrawLine(-d / 2.0, 0);
    DrawArc(d / 6.0, -90, -180);
    DrawLine(d / 2.0, 0);
    MovePen(x, y);
}

void Draw1_4(double d, double x, double y) {
    MovePen(x + 2 * d / 3.0, y - d);
    DrawLine(0, d / 2.0);
    DrawArc(d / 6.0, 0, 180);
    DrawLine(0, -d / 2.0);
    MovePen(x, y);
}

void Draw2_1(double d, double x, double y) {
    MovePen(x, y - d / 3.0);
    DrawLine(d, 0);
    MovePen(x, y - 2 * d / 3.0);
    DrawLine(d, 0);
    MovePen(x, y);
}

void Draw2_2(double d, double x, double y) {
    MovePen(x + d / 3.0, y);
    DrawLine(0, -d);
    MovePen(x + 2 * d / 3.0, y);
    DrawLine(0, -d);
    MovePen(x, y);
}

void Draw3_1(double d, double x, double y) {
    MovePen(x + d / 3.0, y);
    DrawLine(0, -d / 6.0);
    DrawArc(d / 6.0, 0, -90);
    DrawLine(-d / 6.0, 0);
    MovePen(x + 2 * d / 3.0, y);
    DrawLine(0, -d / 2.0);
    DrawArc(d / 6.0, 0, -90);
    DrawLine(-d / 2.0, 0);
    MovePen(x, y);
}

void Draw3_2(double d, double x, double y) {
    MovePen(x + d / 3.0, y);
    DrawLine(0, -d / 2.0);
    DrawArc(d / 6.0, 180, 90);
    DrawLine(d / 2.0, 0);
    MovePen(x + 2 * d / 3.0, y);
    DrawLine(0, -d / 6.0);
    DrawArc(d / 6.0, 180, 90);
    DrawLine(d / 6.0, 0);
    MovePen(x, y);
}

void Draw3_3(double d, double x, double y) {
    MovePen(x + d, y - d / 3.0);
    DrawLine(-d / 2.0, 0);
    DrawArc(d / 6.0, 90, 90);
    DrawLine(0, -d / 2.0);
    MovePen(x + d, y - 2 * d / 3.0);
    DrawLine(-d / 6.0, 0);
    DrawArc(d / 6.0, 90, 90);
    DrawLine(0, -d / 6.0);
    MovePen(x, y);
}

void Draw3_4(double d, double x, double y) {
    MovePen(x, y - d / 3.0);
    DrawLine(d / 2.0, 0);
    DrawArc(d / 6.0, 90, -90);
    DrawLine(0, -d / 2.0);
    MovePen(x, y - 2 * d / 3.0);
    DrawLine(d / 6.0, 0);
    DrawArc(d / 6.0, 90, -90);
    DrawLine(0, -d / 6.0);
    MovePen(x, y);
}

void Draw4_1(double d, double x, double y) {
    MovePen(x + d / 3.0, y);
    DrawLine(0, -d / 6.0);
    DrawArc(d / 6.0, 0, -90);
    DrawLine(-d / 6.0, 0);
    MovePen(x + 2 * d / 3.0, y);
    DrawLine(0, -d);
    MovePen(x, y - 2 * d / 3.0);
    DrawLine(d / 6.0, 0);
    DrawArc(d / 6.0, 90, -90);
    DrawLine(0, -d / 6.0);
    MovePen(x, y);
}

void Draw4_2(double d, double x, double y) {
    MovePen(x + d / 3.0, y);
    DrawLine(0, -d / 6.0);
    DrawArc(d / 6.0, 0, -90);
    DrawLine(-d / 6.0, 0);
    MovePen(x + 2 * d / 3.0, y);
    DrawLine(0, -d / 6.0);
    DrawArc(d / 6.0, 180, 90);
    DrawLine(d / 6.0, 0);
    MovePen(x, y - 2 * d / 3.0);
    DrawLine(d, 0);
    MovePen(x, y);
}

void Draw4_3(double d, double x, double y) {
    MovePen(x + d / 3.0, y);
    DrawLine(0, -d);
    MovePen(x + 2 * d / 3.0, y);
    DrawLine(0, -d / 6.0);
    DrawArc(d / 6.0, 180, 90);
    DrawLine(d / 6.0, 0);
    MovePen(x + d, y - 2 * d / 3.0);
    DrawLine(-d / 6.0, 0);
    DrawArc(d / 6.0, 90, 90);
    DrawLine(0, -d / 6.0);
    MovePen(x, y);
}

void Draw4_4(double d, double x, double y) {
    MovePen(x, y - d / 3.0);
    DrawLine(d, 0);
    MovePen(x, y - 2 * d / 3.0);
    DrawLine(d / 6.0, 0);
    DrawArc(d / 6.0, 90, -90);
    DrawLine(0, -d / 6.0);
    MovePen(x + d, y - 2 * d / 3.0);
    DrawLine(-d / 6.0, 0);
    DrawArc(d / 6.0, 90, 90);
    DrawLine(0, -d / 6.0);
    MovePen(x, y);
}

void Draw5_1(double d, double x, double y) {
    MovePen(x + d / 3.0, y);
    DrawLine(0, -d / 6.0);
    DrawArc(d / 6.0, 0, -90);
    DrawLine(-d / 6.0, 0);
    MovePen(x + 2 * d / 3.0, y);
    DrawLine(0, -d / 6.0);
    DrawArc(d / 6.0, 180, 90);
    DrawLine(d / 6.0, 0);
    MovePen(x, y - 2 * d / 3.0);
    DrawLine(d / 6.0, 0);
    DrawArc(d / 6.0, 90, -90);
    DrawLine(0, -d / 6.0);
    MovePen(x + d, y - 2 * d / 3.0);
    DrawLine(-d / 6.0, 0);
    DrawArc(d / 6.0, 90, 90);
    DrawLine(0, -d / 6.0);
    MovePen(x, y);
}

static void _Render(Sprite *this) {
    double d = this->size.y / 21.0;
    double x = this->position.x, y = this->position.y + this->size.y;

    for (int i = 1; i <= 21; i++) {
        for (int j = 1; j <= 21; j++) {
            if (map1[i][j] == 1) {
                continue;
            } else if (map1[i][j] == 0) {
                if (map1[i + 1][j] == 1 && map1[i - 1][j] == 1 && map1[i][j + 1] == 1 && map1[i][j - 1] == 0) {
                    Draw1_1(d, x - d + j * d, y + d - i * d);
                } else if (map1[i + 1][j] == 1 && map1[i - 1][j] == 0 && map1[i][j + 1] == 1 && map1[i][j - 1] == 1) {
                    Draw1_2(d, x - d + j * d, y + d - i * d);
                } else if (map1[i + 1][j] == 1 && map1[i - 1][j] == 1 && map1[i][j + 1] == 0 && map1[i][j - 1] == 1) {
                    Draw1_3(d, x - d + j * d, y + d - i * d);
                } else if (map1[i + 1][j] == 0 && map1[i - 1][j] == 1 && map1[i][j + 1] == 1 && map1[i][j - 1] == 1) {
                    Draw1_4(d, x - d + j * d, y + d - i * d);
                } else if (map1[i + 1][j] == 1 && map1[i - 1][j] == 1 && map1[i][j + 1] == 0 && map1[i][j - 1] == 0) {
                    Draw2_1(d, x - d + j * d, y + d - i * d);
                } else if (map1[i + 1][j] == 0 && map1[i - 1][j] == 0 && map1[i][j + 1] == 1 && map1[i][j - 1] == 1) {
                    Draw2_2(d, x - d + j * d, y + d - i * d);
                } else if (map1[i + 1][j] == 1 && map1[i - 1][j] == 0 && map1[i][j + 1] == 1 && map1[i][j - 1] == 0) {
                    Draw3_1(d, x - d + j * d, y + d - i * d);
                } else if (map1[i + 1][j] == 1 && map1[i - 1][j] == 0 && map1[i][j + 1] == 0 && map1[i][j - 1] == 1) {
                    Draw3_2(d, x - d + j * d, y + d - i * d);
                } else if (map1[i + 1][j] == 0 && map1[i - 1][j] == 1 && map1[i][j + 1] == 0 && map1[i][j - 1] == 1) {
                    Draw3_3(d, x - d + j * d, y + d - i * d);
                } else if (map1[i + 1][j] == 0 && map1[i - 1][j] == 1 && map1[i][j + 1] == 1 && map1[i][j - 1] == 0) {
                    Draw3_4(d, x - d + j * d, y + d - i * d);
                } else if (map1[i + 1][j] == 0 && map1[i - 1][j] == 0 && map1[i][j + 1] == 1 && map1[i][j - 1] == 0) {
                    Draw4_1(d, x - d + j * d, y + d - i * d);
                } else if (map1[i + 1][j] == 1 && map1[i - 1][j] == 0 && map1[i][j + 1] == 0 && map1[i][j - 1] == 0) {
                    Draw4_2(d, x - d + j * d, y + d - i * d);
                } else if (map1[i + 1][j] == 0 && map1[i - 1][j] == 0 && map1[i][j + 1] == 0 && map1[i][j - 1] == 1) {
                    Draw4_3(d, x - d + j * d, y + d - i * d);
                } else if (map1[i + 1][j] == 0 && map1[i - 1][j] == 1 && map1[i][j + 1] == 0 && map1[i][j - 1] == 0) {
                    Draw4_4(d, x - d + j * d, y + d - i * d);
                } else if (map1[i + 1][j] == 0 && map1[i - 1][j] == 0 && map1[i][j + 1] == 0 && map1[i][j - 1] == 0) {
                    Draw5_1(d, x - d + j * d, y + d - i * d);
                }
            }
        }
    }
}

static void _Collide(Sprite *this, int id, Sprite *other) {
    other->velocity = ZERO_VECTOR;
}

Sprite *ConstructWallsSprite(double left, double height) {
    Sprite *obj = ConstructSprite((Vector2) {left, 0}, (Vector2) {height, height}, ZERO_VECTOR);
    obj->foreColor = "Wall";
    obj->renderer.Render = _Render;
    double d = height / 21.0;
    for (int i = 1; i <= 21; i++) {
        for (int j = 1; j <= 21; j++) {
            if (map1[i][j] == 0) {
                RegisterBoxCollider(obj, DEFAULT_COLLIDER_ID, true, (Vector2) {d, d},
                                    (Vector2) {(j - 1) * d, height - i * d});
            }
        }
    }
    obj->Collide = _Collide;
    return obj;
}