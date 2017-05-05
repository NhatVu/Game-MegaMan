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
		void setPostion(FPOINT p); // top-left position

		float getHeight();
		void setHeight(float h);

		float getWidth();
		void setWidth(float w);		

	protected:
		Node* m_parent = NULL;
		std::vector<Node*> m_children;// chua tat ca con cua no;

		FPOINT m_position;// tọa độ top-left
	
								//
		float m_width = 0;
		float m_height = 0;
	};
}
#endif // !_NODE_H_



