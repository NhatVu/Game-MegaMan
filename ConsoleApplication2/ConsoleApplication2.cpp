#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <time.h>
#include "../SFramework/quadtree/QuadTree.h"
#include "../SFramework/GameObject.h"
#include "../SFramework/SpriteAndAnimation/SpriteSpec.h"
#include "../SFramework/Trace.h"
#include "../MegaMan/Map/MapBombMan.h"
#include "../SFramework/SpriteAndAnimation/TextureManager.h"
#include "../MegaMan/GameObject/MegaMan.h"
#include "../MegaMan/GameObject/State/MegaManIdleState.h"
#include "../SFramework/SpriteAndAnimation/AnimationManager.h"

using namespace s_framework;

void build();
void showListObjectOnscreen();

int main()
{	
	//build();
	showListObjectOnscreen();

	return 0;
}

void build()
{
	TextureManager::SOURCE_TEXTURE_XML = "../MegaMan/Resources/texture.xml";
	TextureManager::SOURCE_TEXTURE_PNG = "../MegaMan/Resources/texture.png";
	TextureManager::SOURCE_MAP_PNG = "../MegaMan/Resources/Cut_Man_map.png";

	AnimationManager::getInstance()->parseAnimationJSON("../MegaMan/Resources/animation.json");

	GameObject* megaMan = new MegaMan();
	megaMan->setTexture(TextureManager::getInstance()->getObjectTexture());
	megaMan->setObjectID(0);
	//((MegaMan*)megaMan)->setState(EState::IDLE);
	//((MegaMan*)megaMan)->setState(new MegaManIdleState());

	// vị trí của mega man trong world
	//ObjectManager::getInstance()->setMegaMan(megaMan);

	MapBombMan* mapBombMan = new MapBombMan("../MegaMan/Resources/map-cut-man.tmx", megaMan);
	mapBombMan->init();

	map<int, GameObject*> map = ObjectManager::getInstance()->getAllObject();
	vector<GameObject*> objs;

	for (std::map<int, GameObject*>::iterator it = map.begin(); it != map.end(); ++it)
	{
		objs.push_back(it->second);
	}

	QuadTree* quadTree = new QuadTree(105 * 32, 69 * 32);
	quadTree->builEmptyQuadTree();
	quadTree->insert(objs);
	quadTree->exportFile();
}

void showListObjectOnscreen()
{
	QuadTree* quadtree = new QuadTree(105 * 32, 69 * 32);
	quadtree->rebuildQuadTree();
	//quadtree->exportFile();
	RECT rect;
	rect.left = 0;
	rect.top = 256;
	rect.right = 256;
	rect.bottom = 0;
	vector<int>* objOnscreen = new vector<int>;
	quadtree->getListObjectOnscreen(rect, objOnscreen);
	for (std::vector<int>::iterator it = objOnscreen->begin(); it != objOnscreen->end(); ++it) {
		cout << *it << '\t';
	}
}