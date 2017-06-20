#include "ViewPort.h"
#include <vector>
#include "../Map/ObjectManager.h"
#include "../../MegaMan/GameObject/MegaMan.h"
using namespace std;
using namespace s_framework;

ViewPort* ViewPort::m_instance = NULL;

ViewPort::ViewPort()
{
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

void ViewPort::updateViewportNextFrame(){
	GameObject* megaMan = ObjectManager::getInstance()->getMegaMan();

	// update theo trục y
#pragma region update viewport theo truc y
	if (((MegaMan*)megaMan)->canChangeViewportUp && (megaMan->getPosition().y - megaMan->getSpriteSpec()->getHeight() / 2 > ViewPort::getInstance()->getPosition().y)){
		// change viewport lên trên
		FPOINT position = ViewPort::getInstance()->getPosition();
		position.y += 2 * 32;
		vector<BOX> listViewportState = ViewPort::getInstance()->getListViewportState();
		for (int i = 0; i < listViewportState.size(); i++){
			BOX temp = listViewportState[i];
			if (megaMan->getPosition().x > temp.x && megaMan->getPosition().x < temp.x + temp.width && position.y < temp.y && position.y > temp.y - temp.height) // điểm y thuộc boundary temp
			{
				ViewPort::getInstance()->setViewportBoundary(temp);
				ViewPort::getInstance()->setPosition(FPOINT(position.x, temp.y));
				megaMan->setPostion(FPOINT(megaMan->getPosition().x, temp.y - temp.height + megaMan->getSpriteSpec()->getHeight() / 2 + 3));
				break;
			}
		}
		Sleep(400);
		//ViewPort::getInstance()->resetViewport(position);

	}
	else
	if (megaMan->getPosition().y - megaMan->getSpriteSpec()->getHeight() / 2 < ViewPort::getInstance()->getPosition().y - ViewPort::getInstance()->getViewportBoundary().height){
		// change viewport xuống dưới
		FPOINT position = ViewPort::getInstance()->getPosition();
		position.y -= 10 * 32;
		vector<BOX> listViewportState = ViewPort::getInstance()->getListViewportState();
		for (int i = 0; i < listViewportState.size(); i++){
			BOX temp = listViewportState[i];
			if (megaMan->getPosition().x > temp.x && megaMan->getPosition().x < temp.x + temp.width && position.y < temp.y && position.y > temp.y - temp.height) // điểm y thuộc boundary temp
			{
				ViewPort::getInstance()->setViewportBoundary(temp);
				ViewPort::getInstance()->setPosition(FPOINT(position.x, temp.y));
				megaMan->setPostion(FPOINT(megaMan->getPosition().x, temp.y + MEGA_MAN_VIRTUAL_HEIGHT / 2 ));
				break;
			}
		}
		Sleep(400);

	}
#pragma endregion

	// update theo trục x. mega man luôn nằm giữa viewport. và viewport.x > min and < max
	FPOINT viewportPos = this->getPosition();
	BOX viewportBoundary = this->getViewportBoundary();

	if (viewportPos.x ==3088)
		return;
	if (megaMan->getPosition().x - SCREEN_WIDTH / 2 < viewportBoundary.x) // không cho di chuyển quá min viewport
		viewportPos.x = viewportBoundary.x;
	else if (megaMan->getPosition().x + SCREEN_WIDTH / 2> viewportBoundary.x + viewportBoundary.width) // không cho di chuyển quả max viewport
		viewportPos.x = viewportBoundary.x + viewportBoundary.width - SCREEN_WIDTH;
	else
		viewportPos.x = megaMan->getPosition().x - SCREEN_WIDTH/2;
	ViewPort::getInstance()->setPosition(viewportPos);
}