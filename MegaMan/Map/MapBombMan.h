#ifndef _MAP_BOMB_MAN_H
#define _MAP_BOMB_MAN_H
#include "../../SFramework/Scene.h"
#include "../../SFramework/Map/GameMap.h"
#include "../../SFramework/Director.h"
#include <string>

using namespace std;
using namespace s_framework;
class MapBombMan
{
private:
	Scene* scene;
	Texture* texture;
	GameMap* map;
public:
	/*
		GETTER AND SETTER
	*/
	void init();
	MapBombMan(string tmxFile,Texture* texture);
	~MapBombMan();
};

#endif
