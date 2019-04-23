#ifndef PAC_SUPERMAN_VECTOR2_H
#define PAC_SUPERMAN_VECTOR2_H
#define ZERO_VECTOR (Vector2){0, 0}

typedef struct {
    double x;
    double y;
} Vector2;

Vector2 Add(Vector2 v1, Vector2 v2);

Vector2 Multiply(double k, Vector2 v);

#endif //PAC_SUPERMAN_VECTOR2_H
