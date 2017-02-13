#ifndef _NODE_H_
#define _NODE_H_

#include <vector>
#include "Utilities.h"

namespace s_framework{
	class Node
	{
	public:
		Node();
		~Node();

		// render
		virtual void render();
		virtual void update(long delta);

		//virtual void addChild(Node *) = 0;
		void addChild(Node* pChild);
		void removeChild(Node* pChild);
		void removeChild(int index);
		void clearChildren();

		/*--------------------------
		 * GETTERS AND SETTERS
		 -------------------------*/
		FPOINT getPosition();
		void setPostion(FPOINT p);

		float getHeight();
		void setHeight(float h);

		float getWidth();
		void setWidth(float w);

		FPOINT getOffsetToParent();
		void setOffsetToParent(FPOINT offset);

		FPOINT getOffsetToScene();
		

	protected:
		Node* m_parent = NULL;
		std::vector<Node*> m_children;// chua tat ca con cua no;

		FPOINT m_position;// trước mắt là tâm vẽ. tọa độ so với parent.
		FPOINT m_offsetToParent; // vecto tịnh tiến child-parnet
		FPOINT m_offsetToScene; // vecto tịnh tiến child-scene, position + offsetToScene -> ra tọa độ cần vẽ.
								//
		float m_width = 0;
		float m_height = 0;

		private:
			FPOINT calculateOffsetToScene(Node *node);
			void calculateOffsetToScene(); // gọi hàm này trước khi vẽ
			void calculateOffsetToParent(); // tính m_offsetToParent theo m_position và width, height
	};
}
#endif // !_NODE_H_



