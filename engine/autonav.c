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

PathNode *_GetPath(PathNode *last);

static void inline _FreeResources(BinaryHeap *open, BinaryHeap *closed);

static inline bool _PointInRect(Vector2 point, Vector2 rectPos, Vector2 rectSize);

static inline Vector2 _GetTargetPos(Sprite *sprite);

static inline bool _ReachTarget(Sprite *sprite, Vector2 position);

static inline PathNode *_AStarFindPath(Scene *scene, Sprite *sprite);

static double _step = 0.1;
static long _maxNodesCount = 100000;
static Vector2 _borderPos = ZERO_VECTOR;
static Vector2 _borderSize = ZERO_VECTOR;

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
    obj->inPath = false;
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

bool DetectMovable(Scene *scene, Sprite *sprite, Vector2 position) {
    for (SpritesListNode *node = scene->gameSprites.head; node != NULL; node = node->next) {
        Sprite *s = node->element;
        if (s == sprite || !s->visible) continue;
        if (_DetectSpriteCollision(sprite, position, s, s->position)) return false;
    }
    return true;
}

void ChangeMaxNodeCounts(long count) {
    _maxNodesCount = count;
}

void ChangePathfindingStep(double step) {
    _step = step;
}

void ChangePathfindingBorder(Vector2 position, Vector2 size) {
    _borderPos = position;
    _borderSize = size;
}

PathNode *_GetPath(PathNode *last) {
    // 将 PathNode 链表反转以得到路径
    PathNode *prev = NULL;
    while (last) {
        last->inPath = true;
        PathNode *parent = last->parent;
        last->parent = prev;
        prev = last;
        last = parent;
    }
    return prev;
}

static void inline _FreeResources(BinaryHeap *open, BinaryHeap *closed) {
    for (int i = 0; i < open->length; i++) {
        PathNode *node = open->elements[i];
        if (!node->inPath) free(node);
    }
    for (int i = 0; i < closed->length; i++) {
        PathNode *node = closed->elements[i];
        if (!node->inPath) free(node);
    }
    FreeBinaryHeap(open);
    FreeBinaryHeap(closed);
}

static inline bool _PointInRect(Vector2 point, Vector2 rectPos, Vector2 rectSize) {
    Vector2 topRight = VAdd(rectPos, rectSize);
    return point.x >= rectPos.x && point.y >= rectPos.y && point.x <= topRight.x && point.y <= topRight.y;
}

static inline Vector2 _GetTargetPos(Sprite *sprite) {
    AutoNavAgent agent = sprite->navAgent;
    switch (agent.targetType) {
        case SPRITE_TARGET:
            return agent.target.sprite->position;
        case POS_TARGET:
            return agent.target.position;
    }
}

static inline bool _ReachTarget(Sprite *sprite, Vector2 position) {
    AutoNavAgent agent = sprite->navAgent;
    switch (agent.targetType) {
        case SPRITE_TARGET:
            return _DetectSpriteCollision(sprite, position, agent.target.sprite, agent.target.sprite->position);
        case POS_TARGET:
            return _PointInRect(agent.target.position, position, sprite->size);
    }
}

static inline PathNode *_AStarFindPath(Scene *scene, Sprite *sprite) {
    BinaryHeap open, closed;
    InitBinaryHeap(&open, _CompareCost);
    InitBinaryHeap(&closed, _CompareCost);
    Vector2 targetPos = _GetTargetPos(sprite);
    if (!_PointInRect(targetPos, _borderPos, _borderSize)) return NULL;
    if (_ReachTarget(sprite, sprite->position)) return _ConstructPathNode(NULL, 0, 0, sprite->position);
    // 将起点放入 open 列表
    PathNode *start = _ConstructPathNode(NULL, 0, _ManhattanDistance(sprite->position, targetPos), sprite->position);
    HeapInsertElement(&open, start);
    while (open.length != 0 && open.length + closed.length <= _maxNodesCount) {
        // 从 open 列表中弹出 cost 最小的节点，放入 closed 列表
        PathNode *node = HeapPopTop(&open);
        HeapInsertElement(&closed, node);
        // 遍历上下左右四个相邻节点
        for (int x = -1; x <= 1; x++)
            for (int y = -1; y <= 1; y++) {
                if (x + y != 1 && x + y != -1) continue;
                // 计算出绝对位置
                Vector2 neighbor = VAdd(node->position, VMultiply(_step, (Vector2) {x, y}));
                if (!_PointInRect(neighbor, _borderPos, _borderSize)) continue;
                // 如和目标碰撞则寻径结束
                if (_ReachTarget(sprite, neighbor)) {
                    PathNode *path = _GetPath(_ConstructPathNode(node, _step, 0, neighbor));
                    _FreeResources(&open, &closed);
                    return path;
                }
                // 如在 closed 列表内则不必检查
                if (HeapSearchElement(&closed, &neighbor, _PositionEqual)) continue;
                // 检测该位置是否有障碍物
                if (!DetectMovable(scene, sprite, neighbor)) continue;
                // 在 open 列表内查找该节点
                int neighborIndex = HeapSearchIndexOfElement(&open, &neighbor, _PositionEqual);
                if (neighborIndex != ELEMENT_NOT_FOUND) {
                    // 如找到则判断新的路线 g 值是否更小
                    double g = CALC_G_FROM_PARENT(node, _step);
                    PathNode *existingNode = open.elements[neighborIndex];
                    if (g < existingNode->g) {
                        // g 值更小，更新父节点及 g 值
                        existingNode->parent = node;
                        existingNode->g = g;
                        existingNode->cost = g + existingNode->h;
                        HeapUpdateElementByIndex(&open, neighborIndex);
                    }
                } else {
                    // 如未找到则直接加入 open 列表
                    double h = _ManhattanDistance(neighbor, targetPos);
                    HeapInsertElement(&open, _ConstructPathNodeFromParent(node, _step, h, neighbor));
                }
            }
    }
    _FreeResources(&open, &closed);
    return NULL;
}

void FreePath(PathNode *path) {
    while (path) {
        PathNode *next = path->parent;
        free(path);
        path = next;
    }
}

bool UpdatePath(Scene *scene, Sprite *sprite) {
    PathNode *path = _AStarFindPath(scene, sprite);
    if (!path) return false;
    if (!sprite->navAgent.path) FreePath(sprite->navAgent.path);
    sprite->navAgent.path = path;
    sprite->velocity = VMultiply(sprite->navAgent.speed, VNormalize(VSubtract(path->position, sprite->position)));
    return true;
}

void SetNavTargetSprite(Sprite *source, Sprite *target) {
    source->navAgent.targetType = SPRITE_TARGET;
    source->navAgent.target.sprite = target;
}

void SetNavTargetPosition(Sprite *sprite, Vector2 position) {
    sprite->navAgent.targetType = POS_TARGET;
    sprite->navAgent.target.position = position;
}

void SetNavDirectTargetPosition(Sprite *sprite, Vector2 position) {
    sprite->navAgent.targetType = POS_TARGET;
    sprite->navAgent.path = _ConstructPathNode(NULL, 0, 0, position);
    sprite->velocity = VMultiply(sprite->navAgent.speed, VNormalize(VSubtract(position, sprite->position)));
}

void AutoNav(Sprite *sprite, double interval) {
    PathNode *node = sprite->navAgent.path;
    if (!node) return;
    Vector2 currentDist = VSubtract(sprite->position, node->position); // 目前距目标点的距离
    Vector2 nextPos = VAdd(sprite->position, VMultiply(interval / 1000.0, sprite->velocity)); // 下一时刻的位置
    Vector2 nextDist = VSubtract(nextPos, node->position); // 下一时刻距目标点的距离
    // 如下一时刻距目标点的距离比目前距目标点的距离小，表明仍在向目标前进，不更新
    if (!VEqual(sprite->position, node->position) && VLengthSquared(nextDist) < VLengthSquared(currentDist)) return;
    // 否则判定已达到目标点，切换到路径中的下一个节点
    //sprite->position = node->position;
    sprite->navAgent.path = node->parent;
    free(node);
    node = sprite->navAgent.path;
    // 如已达到路线的尽头则停止
    if (!node) sprite->velocity = ZERO_VECTOR;
        // 否则设置速度方向朝向下一个节点
    else sprite->velocity = VMultiply(sprite->navAgent.speed, VNormalize(VSubtract(node->position, sprite->position)));
}

bool
SearchNearestMovable(Scene *scene, Sprite *sprite, Vector2 initPos, double largestDist, double step, Vector2 *output) {
    if (DetectMovable(scene, sprite, initPos)) {
        *output = initPos;
        return true;
    }

    double x = initPos.x, y = initPos.y;
    for (int d = 1; d <= largestDist * step; d++) {
        for (int dy = -d; dy <= d; dy++)
            for (int dx = -d; dx <= d; dx += 2 * d) {
                Vector2 newPos = (Vector2) {x + dx * step, y + dy * step};
                if (DetectMovable(scene, sprite, newPos)) {
                    *output = newPos;
                    return true;
                }
            }

        for (int dx = -d + 1; dx <= d - 1; dx++)
            for (int dy = -d; dy <= d; dy += 2 * d) {
                Vector2 newPos = (Vector2) {x + dx * step, y + dy * step};
                if (DetectMovable(scene, sprite, newPos)) {
                    *output = newPos;
                    return true;
                }
            }
    }
    return false;
}
