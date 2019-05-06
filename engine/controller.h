/**@file controller.h
 * @brief 该文件包含了键盘方向控制器的相关方法。
 */
#ifndef PAC_SUPERMAN_CONTROLLER_H
#define PAC_SUPERMAN_CONTROLLER_H

/**@brief 初始化键盘方向控制器。
 *
 */
void InitController();

/**@brief 获取当前方向向量。
 *
 * @return 当前方向向量
 */
Vector2 GetControllerVector();

/**@brief 获取单位化的当前方向向量。
 *
 * @return 单位化的当前方向向量
 */
Vector2 GetNormalizedControllerVector();

#endif //PAC_SUPERMAN_CONTROLLER_H
