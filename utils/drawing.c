#include <graphics.h>
#include <extgraph.h>
#include "drawing.h"
#include "vector2.h"

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
