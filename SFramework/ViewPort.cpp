#include "ViewPort.h"


using namespace s_framework;

ViewPort* ViewPort::m_instance = NULL;

ViewPort::ViewPort()
{
	//D3DXMatrixIdentity(&m_matrixTransform);
	//m_matrixTransform._22 = -1;
}


ViewPort::~ViewPort()
{
}

ViewPort* ViewPort::getInstance()
{
	if (m_instance == NULL)
		m_instance = new ViewPort();
	return m_instance;
}
FPOINT ViewPort::getPosition()
{
	return m_position;
}

void ViewPort::setPosition(FPOINT p) // set gốc tọa độ của ViewPort
{
	m_position.x = p.x;
	m_position.y = p.y;
}

D3DXVECTOR3 ViewPort::transform(D3DXVECTOR3 pWorld)
{
	//D3DXMatrixIdentity(&render);
	//render._11 = p.x;
	//render._21 = p.y;
	D3DXVECTOR3 result;
	result.x = pWorld.x - m_position.x;
	result.y = -pWorld.y + m_position.y;
	result.z = 1;

	return result;
}