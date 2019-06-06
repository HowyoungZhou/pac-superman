#include <sprite.h>
#include <extgraph.h>
#include <engine.h>
#include <game_RankingList_scene.h>
#include <about_scene.h>
#include <game_instruction_scene.h>
#include <game_home_scene.h>
#include <game_scene.h>
#include "game_menu.h"
#include "menu.h"
#include "imgui.h"

enum GameMenuItem {
    PAUSE = 1, NEW_GAME, RANK, BACK_TO_HOME, EXIT
};

enum HelpMenuItem {
    INSTRUCTION = 1, ABOUT
};

enum MapMemuItem {
    CLASSIC = 1, LOVE_ZJU, PEPPA_PIG, PAC_GHOST
};

static void _OnGameMenuItemSelected(MenuList *sender, int selectedIndex) {
    switch (selectedIndex) {
        case PAUSE:
            IsPaused() ? ResumeGame() : PauseGame();
            break;
        case NEW_GAME:
            NewGame();
            break;
        case RANK:
            PushScene(ConstructRankingListScene());
            break;
        case BACK_TO_HOME:
            ReplaceScene(ConstructHomeScene());
            break;
        case EXIT:
            ExitGraphics();
            break;
        default:
            break;
    }
}

static void _OnHelpMenuItemSelected(MenuList *sender, int selectedIndex) {
    switch (selectedIndex) {
        case INSTRUCTION:
            PushScene(ConstructInstructionScene());
            break;
        case ABOUT:
            PushScene(ConstructAboutScene());
            break;
        default:
            break;
    }
}

static void _OnMapMenuItenSelected(MenuList *sender, int selectedIndex) {
    switch (selectedIndex) {
        case CLASSIC:
            ReplaceScene(ConstructGameScene("maps/classic"));
            break;
        case LOVE_ZJU:
            ReplaceScene(ConstructGameScene("maps/lovezju"));
            break;
        case PEPPA_PIG:
            ReplaceScene(ConstructGameScene("maps/peppa_pig"));
            break;
        case PAC_GHOST:
            ReplaceScene(ConstructGameScene("maps/pac_ghost"));
            break;
        default:
            break;
    }
}

static void _UpdateGameMenuList(MenuList *this) {
    this->menuItems[PAUSE] = IsPaused() ? "Resume          | Ctrl-P" : "Pause             | Ctrl-P";
}

Sprite *ConstructGameMenuSprite() {
    MenuList *gameMenu = ConstructMenuList(GenUIID(0), _OnGameMenuItemSelected, 6,
                                           "Game",
                                           "Pause             | Ctrl-P",
                                           "New Game      | Ctrl-N",
                                           "Rank",
                                           "Back to Home",
                                           "Exit                 | Ctrl-E");
    gameMenu->UpdateMenuList = _UpdateGameMenuList;
    MenuList *mapMenu = ConstructMenuList(GenUIID(0), _OnMapMenuItenSelected, 5,
                                          "Map",
                                          "Classic",
                                          "Love ZJU",
                                          "Peppa Pig",
                                          "Pac Ghost");
    MenuList *helpMenu = ConstructMenuList(GenUIID(0), _OnHelpMenuItemSelected, 3,
                                           "Help",
                                           "Instruction | Ctrl-I",
                                           "About");
    Menu *menu = ConstructMenu(3, gameMenu, mapMenu, helpMenu);
    menu->heightRatio = 2.;
    menu->style = (Style) {"Wall", "White", "White", "Wall", true};
    Sprite *obj = ConstructMenuSprite(menu);
    return obj;
}
