#include "Node.h"
#include "SFramework.h"

using namespace s_framework;

Node::Node()
{
}


Node::~Node()
{
}



void Node::addChild(Node* pChild)
{
	m_children.push_back(pChild);
	pChild->m_parent = this;

	// tính lại offset to scene cho parent and child
	//pChild->calculateOffsetToParent();
	//pChild->calculateOffsetToScene();
}

void Node::removeChild(Node* pChild)
{
	for (int i = 0; i < m_children.size(); i++){
		if (m_children[i] == pChild)
		{
			removeChild(i);
		}
	}
}

void Node::removeChild(int index)
{
	Node* p = m_children[index];
	m_children.erase(m_children.begin() + index);
	SAFE_DELETE(p);
}

void Node::clearChildren()
{
	for (int i = 0; i < m_children.size(); i++){
		removeChild(i);
	}
}

void Node::render()
{
	for (int i = 0; i < m_children.size(); i++){
		m_children[i]->render();
	}
}

void Node::update(long delta){
	for (int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->update(delta);
	}
}

FPOINT Node::getPosition()
{
	return m_position;
}

void Node::setPostion(FPOINT p)
{
	//FPOINT delta = p - m_position;
	
	// tịnh tiến tọa độ position của con theo cha.
	// trường hợp này là cha có nhiều con. khi cha di chuyển (yêu cầu thiết lập lại position)
	// thì con cũng phải di chuyển theo cha -> cũng cần thiết lập lại position. Phép tịnh tiến.
	/*for (int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->setPostion(delta + m_position);
	}*/
	m_position = p; // thiết lập lại position của cha
	//calculateOffsetToParent();// tính lại offset của child vs parent
	//calculateOffsetToScene();
}

float Node::getHeight()
{
	return m_height;
}

void Node::setHeight(float h)
{
	m_height = h;
}

float Node::getWidth()
{
	return m_width;
}

void Node::setWidth(float w)
{
	m_width = w;
}

//FPOINT  Node::getOffsetToParent()
//{
//	return m_offsetToParent;
//}
//
//void  Node::setOffsetToParent(FPOINT offset)
//{
//	m_offsetToParent = offset;
//}
//
//FPOINT Node::getOffsetToScene()
//{
//	calculateOffsetToScene();
//	return m_offsetToScene;
//}
//
//void Node::calculateOffsetToScene()
//{
//	m_offsetToScene = calculateOffsetToScene(this);
//	for (int i = 0; i < m_children.size(); i++)
//	{
//		m_children[i]->m_offsetToScene = m_children[i]->calculateOffsetToScene(m_children[i]);
//	}
//}
//
//FPOINT Node::calculateOffsetToScene(Node *node)
//{
//	if (node==NULL || node->m_parent == NULL)
//	{
//		FPOINT a;
//		a.x = 0;
//		a.y = 0;
//		return a;
//	}
//	else
//		return node->m_offsetToParent + calculateOffsetToScene(node->m_parent);
//}
//
//void Node::calculateOffsetToParent()
//{
//	FPOINT originChildInParentCoordinate;
//	originChildInParentCoordinate.x = m_position.x - m_width / 2;
//	originChildInParentCoordinate.y = m_position.y - m_height / 2;
//	
//	m_offsetToParent = originChildInParentCoordinate;
//}

