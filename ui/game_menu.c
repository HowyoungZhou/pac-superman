#include <sprite.h>
#include <extgraph.h>
#include <engine.h>
#include "game_menu.h"
#include "menu.h"
#include "imgui.h"

enum GameMenuItem {
    PAUSE = 1, NEW_GAME, RANK, EXIT
};

enum HelpMenuItem {
    HOW_TO_PLAY = 1, ABOUT
};

enum StyleMenuItem {
    SKIN = 1
};

static void _OnGameMenuItemSelected(MenuList *sender, int selectedIndex) {
    switch (selectedIndex) {
        case PAUSE:
            IsPaused() ? ResumeGame() : PauseGame();
            break;
        case NEW_GAME:
            break;
        case RANK:
            break;
        case EXIT:
            //TODO: Destruct Sprites here...
            ExitGraphics();
            break;
        default:
            break;
    }
}

static void _OnHelpMenuItemSelected(MenuList *sender, int selectedIndex) {
    switch (selectedIndex) {
        case HOW_TO_PLAY:
            break;
        case ABOUT:
            break;
        default:
            break;
    }
}

static void _OnStyleMenuItemSelected(MenuList *sender, int selectedIndex) {
    switch (selectedIndex) {
        case SKIN:
            break;
        default:
            break;
    }
}

static void _UpdateGameMenuList(MenuList *this) {
    this->menuItems[PAUSE] = IsPaused() ? "Resume     | Ctrl-P" : "Pause        | Ctrl-P";
}

Sprite *ConstructGameMenuSprite() {
    MenuList *gameMenu = ConstructMenuList(GenUIID(0), _OnGameMenuItemSelected, 5,
                                           "Game",
                                           "Pause        | Ctrl-P",
                                           "New Game",
                                           "Rank",
                                           "Exit            | Ctrl-E");
    gameMenu->UpdateMenuList = _UpdateGameMenuList;
    MenuList *helpMenu = ConstructMenuList(GenUIID(0), _OnHelpMenuItemSelected, 3,
                                           "Help",
                                           "How To Play?",
                                           "About");
    MenuList *styleMenu = ConstructMenuList(GenUIID(0), _OnStyleMenuItemSelected, 2,
                                           "Style",
                                           "Skin");

    Menu *menu = ConstructMenu(3, gameMenu, helpMenu,styleMenu);
    menu->heightRatio = 2.;
    menu->style = (Style) {"Wall", "White", "White", "Wall", true};
    Sprite *obj = ConstructMenuSprite(menu);
    return obj;
}
