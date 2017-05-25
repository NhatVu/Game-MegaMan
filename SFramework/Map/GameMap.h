#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>
#include <algorithm>

#include "../GameObject.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "../rapidxml-1.13/rapidxml.hpp"
#include "ObjectManager.h"
using namespace  rapidxml;
using namespace std;
//#include "GameGlobal.h"
namespace s_framework {

	class GameMap
	{
	public:
		GameMap(char* filePath); // texture de goi ham object->setTexture
		~GameMap();

	private:
		vector<Node*> mapNode;
		void parseBackground();
		void parseObjectGroup();
		char* filePath;
		int mapHeight;
	};

}
#endif
