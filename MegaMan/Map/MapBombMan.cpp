#include "MapBombMan.h"


MapBombMan::MapBombMan(char* tmxFile, Texture* texture, GameObject* megaMan)
{
	scene = new Scene();
	this->texture = texture;
	this->map = new GameMap(tmxFile, texture);
	this->megaMan = megaMan;
}


MapBombMan::~MapBombMan()
{
	if (scene != NULL)
		delete scene;
	if (this->map != NULL)
		delete this->map;
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