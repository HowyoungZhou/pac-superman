#ifndef PAC_SUPERMAN_DRAWING_H
#define PAC_SUPERMAN_DRAWING_H

#include "vector2.h"

void DrawVectorRectangle(Vector2 position, Vector2 size);

void DrawRectangle(double x, double y, double width, double height);

void DrawCircle(double x, double y, double radius);

void DrawVectorCircle(Vector2 centre, double radius);

void TurnPolarAngle(double angle);

void TurnPolarAngleTo(double angle);

double GetPolarAngle();

void MovePolarPen(double distance);

void DrawPolarLine(double distance);

#endif //PAC_SUPERMAN_DRAWING_H
