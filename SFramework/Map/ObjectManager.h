﻿#ifndef _OBJECT_MANAGER_H_
#define _OBJECT_MANAGER_H_

#include <map>
#include <vector>
#include "../GameObject.h"

using namespace std;
namespace s_framework {

	class ObjectManager
	{
	private:
		static ObjectManager* instance;

		// Quadtree. lưu quadtree vào objectmanager luôn. sau này chỉ cần gọi 
		std::map<int, GameObject*> quadtreeBackground;
		std::map<int, GameObject*> quadtreeStaticObject;
		std::map<int, GameObject*> quadtreeDynamicObject;
		std::map<int, GameObject*> activeObject; // bao gồm cả static và dynamic. active khi nằm trong camara. Đây thực chất 
		// là danh sách sẽ xử lý va chạm
		std::map<int, GameObject*> allObject; // tất cả object trong map
		std::map<int, GameObject*> allBackground;
		ObjectManager();
	public:

		map<int, GameObject*>& getAllObject(){ return this->allObject; }
		void setAllObject(map<int, GameObject*> allObject){
			this->allObject = allObject;
		}

		map<int, GameObject*>& getAllBackground(){ return this->allBackground; }
		void setAllBackground(map<int, GameObject*> background){
			this->allBackground = background;
		}
		/*void addOneToAllBackground(int id, GameObject* gameobject){
			allBackground[id] = gameobject;
		}*/

		map<int, GameObject*> getActiveObject(){ return this->activeObject; }
		void setActiveObject(map<int, GameObject*> activeObject){
			this->activeObject = activeObject;
		}

		// 3. sẽ xử lý quadtree -> lấy được quadtreeBackground,quadtreeStaticObject,quadtreeDynamicObject
		// 2. remove đối tượng nằm ngoài viewport ra khỏi activeObject
		// từ đó lấy được activeObject. (nếu objectID chưa có trong activeObject -> tạo mới. có rồi thì thôi) kèm với điều kiện object đó phải nằm gọn trong viewport
		void processQuadTreeAndViewport(FPOINT viewportPosition);
		static ObjectManager* getInstance();
		~ObjectManager();
	};
}
#endif // !_OBJECT_MANAGER_H_



