#include <math.h>
#include "vector2.h"

Vector2 VAdd(Vector2 v1, Vector2 v2) {
    return (Vector2) {v1.x + v2.x, v1.y + v2.y};
}

Vector2 VSubtract(Vector2 v1, Vector2 v2) {
    return (Vector2) {v1.x - v2.x, v1.y - v2.y};
}

Vector2 V2DScale(Vector2 v1, Vector2 v2) {
    return (Vector2) {v1.x * v2.x, v1.y * v2.y};
}

Vector2 VMultiply(double k, Vector2 v) {
    return (Vector2) {k * v.x, k * v.y};
}

double VLengthSquared(Vector2 v) {
    return v.x * v.x + v.y * v.y;
}

double VLength(Vector2 v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

Vector2 VNormalize(Vector2 v) {
    double length = VLength(v);
    return length == 0 ? ZERO_VECTOR : VMultiply(1. / length, v);
}

double VDistance(Vector2 p1, Vector2 p2) {
    return VLength(VSubtract(p1, p2));
}

Vector2 VAbs(Vector2 v) {
    return (Vector2) {fabs(v.x), fabs(v.y)};
}

Vector2 VMax(Vector2 v1, Vector2 v2) {
    return (Vector2) {fmax(v1.x, v2.x), fmax(v1.y, v2.y)};
}

double VAngle(Vector2 v){
    if(v.x==0 && v.y==0) return 0;
    if(v.x>=0 && v.y>=0  || v.x>=0 && v.y<0)
        return atan(v.y/v.x) * 180 / M_PI;
    if(v.x<0 && v.y>=0 || v.x<0 && v.y<0)
        return atan(v.y/v.x) * 180 / M_PI + 180;
}