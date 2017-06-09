#include "MapBombMan.h"
#include "../../SFramework/Camera/ViewPort.h"
#include "../../SFramework/Map/ObjectManager.h"
MapBombMan::MapBombMan(char* tmxFile, GameObject* megaMan)
{
	int a = 5;
	scene = new Scene();
	this->map = new GameMap(tmxFile);
	this->megaMan = megaMan;


	// 1 map chứa viewport state, gồm id và Box
	BOX viewportState1 = BOX(0, 7 * 32, 57 * 32, 8 * 32); // trừ thanh tiêu đề ra 32px
	BOX viewportState2 = BOX(48 * 32, 14 * 32, 8.5f * 32, 7 * 32);
	BOX viewportState3 = BOX(48 * 32, 21 * 32, 49 * 32, 7 * 32);

	listViewportState.push_back(viewportState1);
	listViewportState.push_back(viewportState2);
	listViewportState.push_back(viewportState3);
}


MapBombMan::~MapBombMan()
{
	if (scene != NULL)
		delete scene;
	if (this->map != NULL)
		delete this->map;
	/*for (auto const &ent1 : mapViewport){
		delete ent1.second;
	}*/
}

void MapBombMan::init(){ 
	std::map<int,GameObject*> mapNode = ObjectManager::getInstance()->getAllBackground();
	for (std::map<int, GameObject*>::iterator it = mapNode.begin(); it != mapNode.end(); ++it) {
		scene->addChild(it->second);
	}
	scene->addChild(megaMan);

	// add sceen to Dircector
	ObjectManager::getInstance()->getAllObject()[0] = megaMan;
	Director::getInstance()->setScene(scene);

	// Init viewport
	ViewPort::getInstance()->setListViewportState(listViewportState);
	ViewPort::getInstance()->setViewportBoundary(BOX(0, 7 * 32, 57 * 32, 8 * 32));
	ViewPort::getInstance()->setPosition(FPOINT(0, 7 * 32));
}