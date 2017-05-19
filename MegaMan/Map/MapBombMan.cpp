#include "MapBombMan.h"


MapBombMan::MapBombMan(char* tmxFile, Texture* texture, GameObject* megaMan)
{
	scene = new Scene();
	this->texture = texture;
	this->map = new GameMap(tmxFile, texture);
	this->megaMan = megaMan;


	// 1 map chứa viewport state, gồm id và Box
	BOX viewportState1 = BOX(0, 0, 57 * 32, 8 * 32); // trừ thanh tiêu đề ra 32px
	BOX viewportState2 = BOX(48 * 32, 7 * 32, 8.5f * 32, 7 * 32);
	BOX viewportState3 = BOX(48 * 32, 15 * 32, 49 * 32, 7 * 32);

	mapViewport[FPOINT(0, 0)] = viewportState1;
	mapViewport[FPOINT(48 * 32, 7 * 32)] = viewportState2;
	mapViewport[FPOINT(48 * 32, 15 * 32)] = viewportState3;


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
	vector<Node*> mapNode = map->getNodesBackground();
	for (int i = 0; i < mapNode.size(); i++){
		scene->addChild(mapNode[i]);
	}
	scene->addChild(megaMan);

	vector<GameObject*> mListObject = map->getListObject();
	//map->sortListObject();
	scene->addGameObject(megaMan);
	scene->addGameObjects(mListObject);
	// add sceen to Dircector
	Director::getInstance()->setScene(scene);
}