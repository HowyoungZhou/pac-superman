#ifndef PAC_SUPERMAN_AUTONAV_H
#define PAC_SUPERMAN_AUTONAV_H

#define INIT_NAV_AGENT (AutoNavAgent) {.speed = 1., .path = NULL}

typedef struct Scene Scene;

typedef enum {
    SPRITE_TARGET, POS_TARGET
} TargetType;

typedef struct PathNode {
    struct PathNode *parent;
    double cost;
    double g;
    double h;
    Vector2 position;
    bool inPath;
} PathNode;

typedef struct AutoNavAgent {
    union {
        Sprite *sprite;
        Vector2 position;
    } target;
    TargetType targetType;
    PathNode *path;
    double speed;
} AutoNavAgent;

/**@brief 修改寻径时的步长。
 *
 * 步长较短会导致寻径时间延长，步长较长可能会导致无法找到路径。
 *
 * @param step 新的步长值
 */
void ChangePathfindingStep(double step);

/**@brief 更新某 Sprite 的自动导航路径。
 *
 * @param scene 当前场景
 * @param sprite 要执行自动导航的 Sprite
 * @return 如果成功找到路径则返回 true，否则返回 false
 */
bool UpdatePath(Scene *scene, Sprite *sprite);

/**@brief 设置某 Sprite 的自动导航的目标 Sprite。
 *
 * @param source 要执行自动导航的 Sprite
 * @param target 目标 Sprite
 */
void SetNavTargetSprite(Sprite *source, Sprite *target);

/**@brief 设置某 Sprite 的自动导航的目标位置。
 *
 * @param sprite 要执行自动导航的 Sprite
 * @param position 目标位置
 */
void SetNavTargetPosition(Sprite *sprite, Vector2 position);

void SetNavDirectTargetPosition(Sprite *sprite, Vector2 position);

/**@brief 自动导航方法，该方法由引擎调用。
 *
 * @param sprite 要执行自动导航的 Sprite
 * @param interval 当前渲染周期
 */
void AutoNav(Sprite *sprite, double interval);

#endif //PAC_SUPERMAN_AUTONAV_H
