#ifndef PAC_SUPERMAN_TEST_SCENE_H
#define PAC_SUPERMAN_TEST_SCENE_H

#include <dynamic_array.h>

Scene *ConstructGameScene(string mapName);

DynamicArray GetAllWalkableTiles();

void RevivePacMan();

void PowerModeOn();

void NewGame();

Sprite *GetCurrentMap();

#endif //PAC_SUPERMAN_TEST_SCENE_H
