#ifndef PAC_SUPERMAN_VECTOR2_H
#define PAC_SUPERMAN_VECTOR2_H
#define ZERO_VECTOR (Vector2){0, 0}

typedef struct {
    double x;
    double y;
} Vector2;

Vector2 VAdd(Vector2 v1, Vector2 v2);

Vector2 VSubtract(Vector2 v1, Vector2 v2);

Vector2 VMultiply(double k, Vector2 v);

double VLengthSquared(Vector2 v);

double VLength(Vector2 v);

Vector2 VNormalize(Vector2 v);

double VDistance(Vector2 p1, Vector2 p2);

Vector2 VAbs(Vector2 v);

Vector2 VMax(Vector2 v1, Vector2 v2);

double VAngle(Vector2 v);

#endif //PAC_SUPERMAN_VECTOR2_H
