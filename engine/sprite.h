/**@file sprite.h
 * @brief 该文件包含了 Sprite 类的定义及相关方法。
 */
#ifndef PAC_SUPERMAN_SPRITE_H
#define PAC_SUPERMAN_SPRITE_H

#include <stdbool.h>
#include <linked_list.h>
#include "vector2.h"
#include "animator.h"
#include "collider.h"

struct sprite;
typedef struct sprite Sprite;

struct sprite {
    Vector2 position;
    Vector2 size;
    Vector2 velocity;
    bool visible;
    bool hasAnimation;
    void *property;

    union {
        void (*Render)(Sprite *this);

        Animator *animator;
    } renderer;

    CollidersList colliders;

    void (*Update)(Sprite *this, double interval);

    void (*Collide)(Sprite *this, int id, Sprite *other);

    void (*Destruct)(Sprite *this);
};

/**@brief Sprite 的构造函数，要实现自定义的 Sprite 类型往往需要通过此方法创建新的 Sprite。
 *
 * @param position Sprite 的位置
 * @param size Sprite 的大小
 * @param velocity Sprite 的速度，设置为 ZERO_VECTOR 可使 Sprite 静止
 * @return 创建的新 Sprite
 */
Sprite *ConstructSprite(Vector2 position, Vector2 size, Vector2 velocity);

/**@brief Sprite 的默认析构函数。
 *
 * @param this 要析构的 Sprite 对象
 */
void DestructSprite(Sprite *this);

/**@brief 注册一个碰撞器。
 *
 * @param sprite 碰撞器所属的 Sprite
 * @param collider 要注册的碰撞器
 */
void RegisterCollider(Sprite *sprite, Collider *collider);

/**@brief 删除一个碰撞器。
 *
 * @param sprite 碰撞器所属的 Sprite
 * @param collider 要删除的碰撞器 ID
 */
bool UnregisterCollider(Sprite *sprite, int id);

/**@brief 注册一个盒型（矩形）碰撞器。
 *
 * @param sprite 碰撞器所属的 Sprite
 * @param id 碰撞器的 ID
 * @param solid 碰撞器是否可以穿透
 * @param size 碰撞器的大小
 * @param position 碰撞器的位置
 */
void RegisterBoxCollider(Sprite *sprite, int id, bool solid, Vector2 size, Vector2 position);

/**@brief 注册一个圆形碰撞器。
 *
 * @param sprite 碰撞器所属的 Sprite
 * @param id 碰撞器的 ID
 * @param solid 碰撞器是否可以穿透
 * @param centre 碰撞器的圆心
 * @param radius 碰撞器的半径
 */
void RegisterCircleCollider(Sprite *sprite, int id, bool solid, Vector2 centre, double radius);

/**@brief 计算 Sprite 的中心位置。
 *
 * @param sprite 待计算的 Sprite
 * @return Sprite 的中心位置
 */
Vector2 CalcCentre(Sprite *sprite);

/**@brief 计算 Sprite 的相对中心位置（相对于 Sprite 的左下角）。
 *
 * @param sprite 待计算的 Sprite
 * @return Sprite 的相对中心位置
 */
Vector2 CalcRelativeCentre(Sprite *sprite);

/**@brief 计算 Sprite 的内切圆半径。
 *
 * @param sprite 待计算的 Sprite
 * @return Sprite 的内切圆半径
 */
double CalcIncircleRadius(Sprite *sprite);

#endif //PAC_SUPERMAN_SPRITE_H
