#ifndef _MAP_BOMB_MAN_H
#define _MAP_BOMB_MAN_H
#include "../../SFramework/Scene.h"
#include "../../SFramework/Map/GameMap.h"
#include "../../SFramework/Director.h"
#include "../../SFramework/GameObject.h"
#include "../GameObject/MegaMan.h"
using namespace s_framework;
class MapBombMan
{
private:
	Scene* scene;
	Texture* texture;
	GameMap* map;
	GameObject* megaMan;
public:
	/*
		GETTER AND SETTER
	*/
	void init();
	MapBombMan(char* tmxFile, Texture* texture, GameObject* megaMan);
	~MapBombMan();
};

#endif
