#include "Director.h"
#include "SFramework.h"

using namespace s_framework;

Director* Director::m_instance = NULL;

Director::Director()
{
	D3DXCreateSprite(SFramework::getInstance()->getDirect3DDevice(), &m_spriteHandler);
	
	m_scene = nullptr;
}


Director::~Director()
{
}

Director* Director::getInstance()
{
	if (m_instance == NULL)
		m_instance = new Director();
	return m_instance;
}
ID3DXSprite* Director::getD3DXSprite()
{
	return m_spriteHandler;
}
void Director::setScene(Scene* scene)
{
	m_scene = scene;
}

void Director::render()
{
	if (m_scene != nullptr)
		m_scene->render();
}