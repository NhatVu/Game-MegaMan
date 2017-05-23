#ifndef _DIRECTOR_H_
#define _DIRECTOR_H_

#include <d3dx9.h>
#include "Node.h"
#include "Scene.h"

namespace s_framework
{
	class Director
	{
	private:
		static Director* m_instance;
		ID3DXSprite *m_spriteHandler = NULL; // dùng để tạo sprite để gọi hàm draw
		Node* m_scene; // cảnh cần vẽ
		/****  method   *****/
		Director();

	public:
		static Director* getInstance();
		ID3DXSprite* getD3DXSprite();
		void setScene(Scene* scene);
		Node* getScene(){
			return this->m_scene;
		}
		void render();

		~Director();
	};
}
#endif // !_DIRECTOR_H_



