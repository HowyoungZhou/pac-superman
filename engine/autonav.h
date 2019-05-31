#ifndef PAC_SUPERMAN_AUTONAV_H
#define PAC_SUPERMAN_AUTONAV_H

#include "scene.h"

typedef struct PathNode {
    struct PathNode *parent;
    double cost;
    double g;
    double h;
    Vector2 position;
} PathNode;

void ChangePathfindingStep(double step);

PathNode *AStarFindPath(Scene *scene, Sprite *sprite, Sprite *target);

#endif //PAC_SUPERMAN_AUTONAV_H
