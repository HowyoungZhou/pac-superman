#include "vector2.h"

Vector2 Add(Vector2 v1, Vector2 v2) {
    return (Vector2) {v1.x + v2.x, v1.y + v2.y};
}

Vector2 Multiply(double k, Vector2 v) {
    return (Vector2) {k * v.x, k * v.y};
}
