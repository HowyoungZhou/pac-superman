#include <math.h>
#include "vector2.h"

Vector2 Vector2Add(Vector2 v1, Vector2 v2) {
    return (Vector2) {v1.x + v2.x, v1.y + v2.y};
}

Vector2 Vector2Multiply(double k, Vector2 v) {
    return (Vector2) {k * v.x, k * v.y};
}

double Vector2Length(Vector2 v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

Vector2 Vector2Normalize(Vector2 v) {
    double length = Vector2Length(v);
    return length == 0 ? ZERO_VECTOR : Vector2Multiply(1. / length, v);
}
