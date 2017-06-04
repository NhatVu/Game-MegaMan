#include "ObjectManager.h"
#include "../../MegaMan/MegaManUtilities.h"
using namespace s_framework;

ObjectManager* ObjectManager::instance = NULL;
int ObjectManager::notInMapObjectId = 1000;
ObjectManager::ObjectManager()
{
}

void s_framework::ObjectManager::loadQuadtreeFromFile()
{
}

void s_framework::ObjectManager::createObjectOnScreen()
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
	for (map<int, GameObject*>::iterator it = quadtreeBackground.begin(); it != quadtreeBackground.end();) {
		object = it->second;
		BOX collisionBox = object->getCollisionBox();
		if ((collisionBox.x > cameraBox.x + cameraBox.width) || (collisionBox.x + collisionBox.width < cameraBox.x)
			|| (collisionBox.y < cameraBox.y - cameraBox.height) || (collisionBox.y - collisionBox.height > cameraBox.y)){
			object->resetToInit();
			quadtreeBackground.erase(it++);
		}
		else{
			++it;
		}
	}
	// loại bỏ những object trong activeObject nằm ngoài camera
	for (map<int, GameObject*>::iterator it = activeObject.begin(); it != activeObject.end();) {
		object = it->second;
		int a = object->getState();
		if (object->getState() == EState::DIE){
			int a = 5;
		}
		BOX collisionBox = object->getCollisionBox();
		// object trong activeObject nằm ngoài camera => remove
		if ((collisionBox.x > cameraBox.x + cameraBox.width) || (collisionBox.x + collisionBox.width < cameraBox.x)
			|| (collisionBox.y < cameraBox.y - cameraBox.height) || (collisionBox.y - collisionBox.height > cameraBox.y)){
			if (object->getType() == ECharacter::MEGAMAN){
				++it;
				continue;
			}
			if (object->getState() == EState::DIE){
				int a = 5;
			}
			if (object->getType() == ECharacter::BLADER){
				int a = 5;
			}
			object->resetToInit();
			collisionBox = object->getCollisionBox();
			// nếu init box nằm trong camera -> Inactive
			if (!((collisionBox.x > cameraBox.x + cameraBox.width) || (collisionBox.x + collisionBox.width < cameraBox.x)
				|| (collisionBox.y < cameraBox.y - cameraBox.height) || (collisionBox.y - collisionBox.height > cameraBox.y)))
				object->setIsInactive(true);
			else{
				object->setIsInactive(false); // ra khỏi viewport -> đối tượng active trở lại.
				activeObject.erase(it++);
			}

			if (object->getObjectID() > 999)
				delete object;
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

