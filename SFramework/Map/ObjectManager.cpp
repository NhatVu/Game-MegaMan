#include "ObjectManager.h"

using namespace s_framework;

ObjectManager* ObjectManager::instance = NULL;
ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}

ObjectManager* ObjectManager::getInstance(){
	if (instance == NULL)
		instance = new ObjectManager();
	return instance;
}

//xử lý quadtree và viewport. trả về danh sách active object
void ObjectManager::processQuadTreeAndViewport(FPOINT viewportPosition){
	this->activeObject = this->allObject;
}

