#include <math.h>
#include <graphics.h>
#include <extgraph.h>
#include "drawing.h"
#include "vector2.h"

static double _theta = 0;

void DrawRectangle(double x, double y, double width, double height) {
    MovePen(x, y);
    DrawLine(0, height);
    DrawLine(width, 0);
    DrawLine(0, -height);
    DrawLine(-width, 0);
}

void DrawVectorRectangle(Vector2 position, Vector2 size) {
    DrawRectangle(position.x, position.y, size.x, size.y);
}

void DrawCircle(double x, double y, double radius) {
    MovePen(x + radius, y);
    DrawArc(radius, 0, 360);
}

void DrawVectorCircle(Vector2 centre, double radius) {
    DrawCircle(centre.x, centre.y, radius);
}

void DrawPolarLine(double distance) {
    DrawLine(distance * cos(_theta), distance * sin(_theta));
}

void TurnPolarAngle(double angle) {
    _theta += angle / 180.0 * M_PI;
}

double GetPolarAngle() {
    return _theta * 180.0 / M_PI;
}

void MovePolarPen(double distance) {
    double x = GetCurrentX();
    double y = GetCurrentY();
    MovePen(x + distance * cos(_theta), y + distance * sin(_theta));
}

void TurnPolarAngleTo(double angle) {
    _theta = angle / 180.0 * M_PI;
}
