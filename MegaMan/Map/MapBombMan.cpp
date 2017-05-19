#include "MapBombMan.h"


MapBombMan::MapBombMan(string tmxFile, Texture* texture)
{
	scene = new Scene();
	this->texture = texture;
	this->map = new GameMap(tmxFile, texture);
}


MapBombMan::~MapBombMan()
{
	if (scene != NULL)
		delete scene;
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