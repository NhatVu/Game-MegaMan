#ifndef _MAP_CUT_MAN_H
#define _MAP_CUT_MAN_H_

#include "../../SFramework/Scene.h"
#include "../../SFramework/Map/GameMap.h"
#include "../../SFramework/Director.h"
#include "../../SFramework/GameObject.h"
#include "../GameObject/MegaMan.h"
#include "../../SFramework/Utilities.h"
#include "../MegaManUtilities.h"
#include <map>
#include <vector>
using namespace s_framework;
using namespace std;

class MapCutMan
{
	Scene* scene;
	GameMap* map;
	GameObject* megaMan;
	vector<BOX> listViewportState;
public:
	/*
	GETTER AND SETTER
	*/
	void init();
	MapCutMan(char* tmxFile, GameObject* megaMan);
	~MapCutMan();
};

#endif
