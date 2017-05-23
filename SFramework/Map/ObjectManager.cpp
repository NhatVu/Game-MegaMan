#include "ObjectManager.h"
#include "../../MegaMan/MegaManUtilities.h"
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
	// 1. lấy các đối tượng có thể va chạm với viewport trong quadtree
	this->quadtreeBackground = this->allBackground;
	this->quadtreeObject = this->allObject;
	// 2. từ các đối tường này, chỉ chọn những đối tượng nằm trong camera
	// nếu nằm trong camera và có rồi => khỏi tạo lại. chưa có thì tạo
	// nếu quadtreeObject nằm ngoài camera => remove 
	BOX cameraBox = BOX(viewportPosition.x, viewportPosition.y, SCREEN_WIDTH, SCREEN_HEIGHT);
	GameObject *object;
	// loại bỏ những object trong activeObject nằm ngoài camera
	for (map<int, GameObject*>::iterator it = activeObject.begin(); it != activeObject.end();) {
		object = it->second;
		BOX collisionBox = object->getCollisionBox();
		// object trong activeObject nằm ngoài camera => remove
		if ((collisionBox.x > cameraBox.x + cameraBox.width) || (collisionBox.x + collisionBox.width < cameraBox.x)
			|| (collisionBox.y < cameraBox.y - cameraBox.height) || (collisionBox.y - collisionBox.height > cameraBox.y)){
			object->resetToInit();
			activeObject.erase(it++);
		}
		else
			++it;
	}

	for (map<int, GameObject*>::iterator it = quadtreeObject.begin(); it != quadtreeObject.end(); ++it) {
		object = it->second;
		
		BOX collisionBox = object->getCollisionBox();
		// object trong quadtreeObject nằm ngoài camera
		if ((collisionBox.x > cameraBox.x + cameraBox.width) || (collisionBox.x + collisionBox.width < cameraBox.x)
			|| (collisionBox.y < cameraBox.y - cameraBox.height) || (collisionBox.y - collisionBox.height > cameraBox.y)){
			continue;
		}
		if (it->first == 31){
			int a = 5;
		}
		// nếu chưa tồn tại object trong activeObject => gán vào
		if (activeObject[it->first] == NULL)
			activeObject[it->first] = object;

	}
}

