/**@file animator.h
 * @brief 该文件包含了 Animator 类的定义及相关方法。
 */
#ifndef PAC_SUPERMAN_ANIMATOR_H
#define PAC_SUPERMAN_ANIMATOR_H

#include <stdint.h>
#include <stdbool.h>

struct sprite;
typedef struct sprite Sprite;

struct animator;
typedef struct animator Animator;

typedef uint16_t Frame;

struct animator {
    Frame currentFrame;
    Frame framesCount;
    double interval;
    bool repeated;
    bool reverse;
    bool paused;

    void (*Animate)(Animator *this, Sprite *sprite, Frame frame);

    int intervals[];
};

/**@brief Animator 的构造函数。
 *
 * @param framesCount 动画的总帧数
 * @return 构造的 Animator
 */
Animator *ConstructAnimator(Frame framesCount);

/**@brief Animator 的析构函数。
 *
 * @param this Animator 对象
 */
void DestructAnimator(Animator *this);

/**@brief 暂停动画器。
 *
 * @param this Animator 对象
 */
void PauseAnimator(Animator *this);

/**@brief 继续动画器。
 *
 * @param this Animator 对象
 */
void ResumeAnimator(Animator *this);

/**@brief 重置动画器，重置计时器并从第一帧开始播放。
 *
 * @param this Animator 对象
 */
void ResetAnimator(Animator *this);

/**@brief 更新动画器的计时器，该方法由引擎调用。
 *
 * @param this Animator 对象
 * @param interval 时间间隔
 */
void TickAnimator(Animator *this, double interval);

/**@brief 获得当前实际帧。
 *
 * @param this Animator 对象
 * @return 当前实际帧
 */
Frame GetActualFrame(Animator *this);

#endif //PAC_SUPERMAN_ANIMATOR_H
