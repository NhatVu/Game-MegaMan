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
	m_position = p; // thiết lập lại position của cha
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


