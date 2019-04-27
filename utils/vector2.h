#ifndef PAC_SUPERMAN_VECTOR2_H
#define PAC_SUPERMAN_VECTOR2_H
#define ZERO_VECTOR (Vector2){0, 0}

typedef struct {
    double x;
    double y;
} Vector2;

Vector2 Vector2Add(Vector2 v1, Vector2 v2);

Vector2 Vector2Multiply(double k, Vector2 v);

double Vector2Length(Vector2 v);

Vector2 Vector2Normalize(Vector2 v);

#endif //PAC_SUPERMAN_VECTOR2_H
