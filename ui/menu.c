#include <sprite.h>
#include <genlib.h>
#include <stdarg.h>
#include <graphics.h>
#include <extgraph.h>
#include "menu.h"
#include "imgui.h"

static void _Render(Sprite *this);

static void _Destruct(Sprite *this);

static inline double _CalcLargestStringWidth(string strings[], int n);

static inline double _CalcLargestStringWidth(string strings[], int n) {
    double max = 0;
    for (int i = 0; i < n; i++) {
        double width = TextStringWidth(strings[i]);
        if (width > max)max = width;
    }
    return max;
}

static void _Render(Sprite *this) {
    Menu *menu = this->property;
    setMenuColors(menu->style.borderColor, menu->style.textColor, menu->style.highlightedBorderColor,
                  menu->style.highlightedTextColor, menu->style.filled);
    drawMenuBar(this->position.x, this->position.y, this->size.x, this->size.y); // 绘制外边框
    double x = 0;
    for (int i = 0; i < menu->listsCount; i++) {
        MenuList *list = menu->lists[i];
        if (list->UpdateMenuList != NULL)list->UpdateMenuList(list);
        // 计算菜单按钮宽度，由于默认加上了 FontAscent / 2 的 Padding，所以再加上一个 FontAscent
        double w = TextStringWidth(list->menuItems[0]) + GetFontAscent();
        // 计算菜单宽度，同上需加上一个 FontAscent
        double wlist = _CalcLargestStringWidth(list->menuItems, list->itemsCount) + GetFontAscent();
        int res = menuList(list->id, x, this->position.y, w, wlist, this->size.y, list->menuItems, list->itemsCount);
        if (res > 0 && list->OnMenuItemSelected != NULL)list->OnMenuItemSelected(list, res);
        x += w;
    }
}

static void _Destruct(Sprite *this) {
    DestructMenu(this->property);
    DestructSprite(this);
}

MenuList *ConstructMenuList(int id, OnMenuItemSelectedCallback onMenuItemSelected, unsigned int itemsCount, ...) {
    MenuList *obj = malloc(sizeof(MenuList) + itemsCount * sizeof(string));
    va_list items;
    va_start(items, itemsCount);
    for (int i = 0; i < itemsCount; i++) {
        obj->menuItems[i] = va_arg(items, string);
    }
    va_end(items);
    obj->id = id;
    obj->UpdateMenuList = NULL;
    obj->OnMenuItemSelected = onMenuItemSelected;
    obj->itemsCount = itemsCount;
    return obj;
}

void DestructMenuList(MenuList *list) {
    free(list);
}

Menu *ConstructMenu(unsigned int listsCount, ...) {
    Menu *obj = malloc(sizeof(Menu) + listsCount * sizeof(MenuList));
    va_list lists;
    va_start(lists, listsCount);
    for (int i = 0; i < listsCount; i++) {
        obj->lists[i] = va_arg(lists, MenuList*);
    }
    va_end(lists);
    obj->style = DEFAULT_STYLE;
    obj->listsCount = listsCount;
    obj->heightRatio = 1.5;
    return obj;
}

void DestructMenu(Menu *this) {
    for (int i = 0; i < this->listsCount; i++) {
        DestructMenuList(this->lists[i]);
    }
    free(this);
}

Sprite *ConstructMenuSprite(Menu *menu) {
    Sprite *obj = ConstructSprite((Vector2) {0, GetWindowHeight() - menu->heightRatio * GetFontHeight()},
                                  (Vector2) {GetWindowWidth(), menu->heightRatio * GetFontHeight()},
                                  ZERO_VECTOR);
    obj->property = menu;
    obj->renderer.Render = _Render;
    obj->Destruct = _Destruct;
    return obj;
}
