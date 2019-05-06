/**@file button.h
 * @brief 此文件包含了 Button 类的定义以及相关方法。
 */
#ifndef PAC_SUPERMAN_BUTTON_H
#define PAC_SUPERMAN_BUTTON_H

#include <genlib.h>

typedef void (*OnClickCallback)(Sprite *button);

typedef struct {
    int id;
    string label;
    OnClickCallback OnClick;
} Button;

/**@brief 创建一个按钮 Sprite 对象。
 *
 * @param id 按钮 ID
 * @param position 按钮的位置
 * @param size 按钮的大小
 * @param label 按钮上显示的文本
 * @param onClick 按钮单击事件回调函数
 * @return 创建的按钮 Sprite 对象
 */
Sprite *ConstructButtonSprite(int id, Vector2 position, Vector2 size, string label, OnClickCallback onClick);

#endif //PAC_SUPERMAN_BUTTON_H
