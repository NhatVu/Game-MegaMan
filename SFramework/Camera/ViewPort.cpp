#include "ViewPort.h"
#include <vector>

using namespace std;
using namespace s_framework;

ViewPort* ViewPort::m_instance = NULL;

ViewPort::ViewPort()
{
	//D3DXMatrixIdentity(&m_matrixTransform);
	//m_matrixTransform._22 = -1;
	BOX viewportState1 = BOX(0, 7 * 32, 57 * 32, 8 * 32); // trừ thanh tiêu đề ra 32px
	BOX viewportState2 = BOX(48 * 32, 14 * 32, 8.5f * 32, 7 * 32);
	BOX viewportState3 = BOX(48 * 32, 21 * 32, 49 * 32, 7 * 32);

	listViewportState.push_back(viewportState1);
	listViewportState.push_back(viewportState2);
	listViewportState.push_back(viewportState3);
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

void ViewPort::setPosition(FPOINT p) // set gốc tọa độ của ViewPort, top-left
{
	m_position.x = p.x;
	m_position.y = p.y;
}

D3DXVECTOR3 ViewPort::worldToViewport(D3DXVECTOR3 pWorld)
{
	//D3DXMatrixIdentity(&render);
	//render._11 = p.x;
	//render._21 = p.y;
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = -m_position.x;
	mt._42 = m_position.y;

	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &pWorld, &mt);
	D3DXVECTOR3 result(vp_pos.x, vp_pos.y, 0);
	/*result.x = pWorld.x - m_position.x;
	result.y = -pWorld.y + m_position.y;
	result.z = 1;*/

	return result;
}