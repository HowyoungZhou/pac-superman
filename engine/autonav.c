#include <math.h>
#include "sprite.h"
#include <binary_heap.h>
#include <vector2.h>
#include "scene.h"
#include "autonav.h"

#define CALC_G_FROM_PARENT(parent, distance) (((parent) == NULL ? 0 : (parent)->g) + (distance))

static inline PathNode *_ConstructPathNodeFromParent(PathNode *parent, double distance, double h, Vector2 position);

static inline PathNode *_ConstructPathNode(PathNode *parent, double g, double h, Vector2 position);

static inline double _ManhattanDistance(Vector2 p1, Vector2 p2);

static int _CompareCost(void *p1, void *p2);

static bool _PositionEqual(void *pathNode, void *position);

static inline Collider _CalcAbsoluteCollider(Collider *collider, Vector2 position);

static inline bool _DetectSpriteCollision(Sprite *s1, Vector2 p1, Sprite *s2, Vector2 p2);

static inline bool _DetectMovable(Scene *scene, Sprite *sprite, Vector2 position);

static double _step = 0.1;

static inline PathNode *_ConstructPathNodeFromParent(PathNode *parent, double distance, double h, Vector2 position) {
    return _ConstructPathNode(parent, CALC_G_FROM_PARENT(parent, distance), h, position);
}

static inline PathNode *_ConstructPathNode(PathNode *parent, double g, double h, Vector2 position) {
    PathNode *obj = malloc(sizeof(PathNode));
    obj->parent = parent;
    obj->g = g;
    obj->h = h;
    obj->cost = g + h;
    obj->position = position;
    return obj;
}

static inline double _ManhattanDistance(Vector2 p1, Vector2 p2) {
    return fabs(p1.x - p2.x) + fabs(p1.y - p2.y);
}

static int _CompareCost(void *p1, void *p2) {
    return ((PathNode *) p1)->cost < ((PathNode *) p2)->cost ? -1 : 1;
}

static bool _PositionEqual(void *pathNode, void *position) {
    return VEqual(((PathNode *) pathNode)->position, *((Vector2 *) position));
}

static inline Collider _CalcAbsoluteCollider(Collider *collider, Vector2 position) {
    Collider res = *collider;
    switch (res.type) {
        case BOX_COLLIDER:
            res.shape.boxCollider.position = VAdd(position, res.shape.boxCollider.position);
            break;
        case CIRCLE_COLLIDER:
            res.shape.circleCollider.centre = VAdd(position, res.shape.circleCollider.centre);
            break;
    }
    return res;
}

static inline bool _DetectSpriteCollision(Sprite *s1, Vector2 p1, Sprite *s2, Vector2 p2) {
    if (s1->colliders.head == NULL || s2->colliders.head == NULL) return false;
    for (ColliderNode *n1 = s1->colliders.head; n1 != NULL; n1 = n1->next) {
        if (!((Collider *) n1->element)->solid) continue;
        Collider c1 = _CalcAbsoluteCollider(n1->element, p1);
        for (ColliderNode *n2 = s2->colliders.head; n2 != NULL; n2 = n2->next) {
            if (!((Collider *) n2->element)->solid) continue;
            Collider c2 = _CalcAbsoluteCollider(n2->element, p2);
            if (DetectIntersection(&c1, &c2)) return true;
        }
    }
    return false;
}

static inline bool _DetectMovable(Scene *scene, Sprite *sprite, Vector2 position) {
    for (SpritesListNode *node = scene->gameSprites.head; node != NULL; node = node->next) {
        Sprite *s = node->element;
        if (s == sprite || !s->visible) continue;
        if (_DetectSpriteCollision(sprite, position, s, s->position)) return false;
    }
    return true;
}

void ChangePathfindingStep(double step) {
    _step = step;
}

PathNode *AStarFindPath(Scene *scene, Sprite *sprite, Sprite *target) {
    BinaryHeap open, closed;
    InitBinaryHeap(&open, _CompareCost);
    InitBinaryHeap(&closed, _CompareCost);
    HeapInsertElement(&open, _ConstructPathNode(NULL, 0, _ManhattanDistance(sprite->position, target->position),
                                                sprite->position));
    while (open.length != 0) {
        PathNode *node = HeapPopTop(&open);
        HeapInsertElement(&closed, node);
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                if (x + y != 1 && x + y != -1) continue;
                Vector2 neighbor = VAdd(node->position, VMultiply(_step, (Vector2) {x, y}));
                if (_DetectSpriteCollision(sprite, neighbor, target, target->position)) {
                    FreeBinaryHeap(&open);
                    FreeBinaryHeap(&closed);
                    return _ConstructPathNode(node, _step, _ManhattanDistance(neighbor, target->position),
                                              neighbor);
                }

                if (!_DetectMovable(scene, sprite, neighbor)) continue;
                if (HeapSearchElement(&closed, &neighbor, _PositionEqual)) continue;

                PathNode *existingNeighbor = HeapPopElement(&open, &neighbor, _PositionEqual);
                int neighborIndex = HeapSearchIndexOfElement(&open, &neighbor, _PositionEqual);
                if (neighborIndex != ELEMENT_NOT_FOUND) {
                    double g = CALC_G_FROM_PARENT(node, _step);
                    PathNode *existingNode = open.elements[neighborIndex];
                    if (g < existingNode->g) {
                        existingNeighbor->parent = node;
                        existingNeighbor->g = g;
                        existingNeighbor->cost = g + existingNeighbor->h;
                        HeapUpdateElementByIndex(&open, neighborIndex);
                    }
                } else {
                    double h = _ManhattanDistance(neighbor, target->position);
                    HeapInsertElement(&open, _ConstructPathNodeFromParent(node, _step, h, neighbor));
                }
            }
        }
    }
    FreeBinaryHeap(&open);
    FreeBinaryHeap(&closed);
    return NULL;
}
