#ifndef _MAP_BOMB_MAN_H
#define _MAP_BOMB_MAN_H
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
class MapBombMan
{
private:
	Scene* scene;
	Texture* texture;
	GameMap* map;
	GameObject* megaMan;
	vector<BOX> listViewportState;
public:
	/*
		GETTER AND SETTER
	*/
	void init();
	MapBombMan(char* tmxFile, Texture* texture, GameObject* megaMan);
	~MapBombMan();
};

#endif
