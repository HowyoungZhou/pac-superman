#ifndef PAC_SUPERMAN_AUTONAV_H
#define PAC_SUPERMAN_AUTONAV_H

#define INIT_NAV_AGENT (AutoNavAgent){NULL, 1.}

typedef struct Scene Scene;

typedef struct PathNode {
    struct PathNode *parent;
    double cost;
    double g;
    double h;
    Vector2 position;
    bool inPath;
} PathNode;

typedef struct AutoNavAgent {
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

/**@brief 设置某 Sprite 的自动导航目标。
 *
 * @param scene 当前场景
 * @param source 要执行自动导航的 Sprite
 * @param target 目标 Sprite
 * @return 如果成功找到路径则返回 true，否则返回 false
 */
bool SetNavTargetSprite(Scene *scene, Sprite *source, Sprite *target);

/**@brief 自动导航方法，该方法由引擎调用。
 *
 * @param sprite 要执行自动导航的 Sprite
 * @param interval 当前渲染周期
 */
void AutoNav(Sprite *sprite, double interval);

#endif //PAC_SUPERMAN_AUTONAV_H
