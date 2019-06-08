#ifndef PAC_SUPERMAN_TEST_SCENE_H
#define PAC_SUPERMAN_TEST_SCENE_H

#include <dynamic_array.h>

typedef struct {
    Sprite *map;
    Sprite *pacman;
    Sprite *blinky;
    Sprite *pinky;
    Sprite *inky;
    Sprite *clyde;
} Heros;

Scene *ConstructGameScene(string mapName);

DynamicArray GetAllWalkableTiles();

void RevivePacMan();

void PowerModeOn();

void NewGame();

Heros * GetCurrentHeros();

#endif //PAC_SUPERMAN_TEST_SCENE_H
