#ifndef PAC_SUPERMAN_MENU_H
#define PAC_SUPERMAN_MENU_H

#include <genlib.h>
#include "style.h"

struct MenuList;

typedef void (*OnMenuItemSelectedCallback)(struct MenuList *sender, int selectedIndex);

typedef struct MenuList {
    int id;
    unsigned int itemsCount;

    void (*UpdateMenuList)(struct MenuList *this);

    OnMenuItemSelectedCallback OnMenuItemSelected;

    string menuItems[];
} MenuList;

typedef struct {
    unsigned int listsCount;
    double heightRatio;
    Style style;
    MenuList *lists[];
} Menu;

MenuList *ConstructMenuList(int id, OnMenuItemSelectedCallback onMenuItemSelected, unsigned int itemsCount, ...);

void DestructMenuList(MenuList *list);

Menu *ConstructMenu(unsigned int listsCount, ...);

void DestructMenu(Menu *this);

Sprite *ConstructMenuSprite(Menu *menu);

#endif //PAC_SUPERMAN_MENU_H
