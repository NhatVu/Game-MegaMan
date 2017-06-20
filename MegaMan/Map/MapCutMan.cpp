#include "MapCutMan.h"
#include "../../SFramework/Camera/ViewPort.h"
#include "../../SFramework/Map/ObjectManager.h"
MapCutMan::MapCutMan(char* tmxFile, GameObject* megaMan)
{
	scene = new Scene();
	this->map = new GameMap(tmxFile);
	this->megaMan = megaMan;


	// 1 map chứa viewport state, gồm id và Box
	//BOX viewportState1 = BOX(0, 7 * 32, 57 * 32, 8 * 32); // trừ thanh tiêu đề ra 32px
	listViewportState.push_back( BOX(0, 7 * 32, 32 * 32, 7 * 32)); // stage 1

	listViewportState.push_back(BOX(24 * 32, 14.5f * 32, 9 * 32, 7 * 32)); // stage 2
	listViewportState.push_back(BOX(24 * 32, 22 * 32, 8 * 32, 7 * 32)); // stage 3
	listViewportState.push_back(BOX(24 * 32, 29.5f * 32, 9 * 32, 7 * 32));
	listViewportState.push_back(BOX(24 * 32, 37 * 32, 24 * 32, 7 * 32));
	listViewportState.push_back(BOX(40 * 32, 44.5f * 32, 9 * 32, 7 * 32));
	listViewportState.push_back(BOX(40 * 32, 52 * 32, 9 * 32, 7 * 32));
	listViewportState.push_back(BOX(40 * 32, 59.5 * 32, 9 * 32, 7 * 32));
	listViewportState.push_back(BOX(40 * 32, 67 * 32, 24 * 32, 7 * 32)); // stage cao nhất

	listViewportState.push_back(BOX(55 * 32, 59.5f * 32,  9* 32, 7 * 32));
	listViewportState.push_back(BOX(55 * 32, 52 * 32, 9 * 32, 7 * 32));
	listViewportState.push_back(BOX(55 * 32, 44.5f * 32, 50.5 * 32, 7 * 32));
	
}


MapCutMan::~MapCutMan()
{
	if (scene != NULL)
		delete scene;
	if (this->map != NULL)
		delete this->map;
	/*for (auto const &ent1 : mapViewport){
	delete ent1.second;
	}*/
}

void MapCutMan::init(){
	std::map<int, GameObject*> mapNode = ObjectManager::getInstance()->getAllBackground();
	for (std::map<int, GameObject*>::iterator it = mapNode.begin(); it != mapNode.end(); ++it) {
		scene->addChild(it->second);
	}
	scene->addChild(megaMan);

	// add sceen to Dircector
	ObjectManager::getInstance()->getAllObject()[0] = megaMan;
	Director::getInstance()->setScene(scene);

	// Init viewport
	ViewPort::getInstance()->setListViewportState(listViewportState);
	ViewPort::getInstance()->setViewportBoundary(BOX(0, 7 * 32, 32 * 32, 8 * 32));
	ViewPort::getInstance()->setPosition(FPOINT(0, 7 * 32));
}