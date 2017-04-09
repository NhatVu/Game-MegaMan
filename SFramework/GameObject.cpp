#include "GameObject.h"
#include "SFramework.h"
#include "Director.h"
#include "Texture.h"
#include "ViewPort.h"
#include "Trace.h"

using namespace s_framework;

GameObject::GameObject()
{
	
}


GameObject::~GameObject()
{
	//SAFE_DELETE(m_spriteSpec);
	// khong được delet texture or spriteSpec vì nó được set từ bên ngoài. ko new trong nội bộ object.
	// resource cho toàn bộ app
}

void GameObject::setTexture(Texture* texture){
	m_texture = texture;
}

void GameObject::setSpriteSpec(SpriteSpec* spriteSpec){
	m_spriteSpec = spriteSpec;
}

void GameObject::render()
{

	// đang xét trục y hướng xuống. 
	// có vẽ theo tâm hay không ? tâm quay gì gì đó.
	ID3DXSprite *spriteHandler;
	spriteHandler = Director::getInstance()->getD3DXSprite();

	RECT srcRect;
	srcRect.left = m_spriteSpec->getX();
	//trace(""+ srcRect.left);
	srcRect.top = m_spriteSpec->getY();
	//trace("" + srcRect.top);
	srcRect.right = srcRect.left + m_spriteSpec->getWidth();
	srcRect.bottom = srcRect.top + m_spriteSpec->getHeight();

	
	// tâm của frame. tọa độ top = 0. left = 0
	D3DXVECTOR3 centerOfSpriteTexture = D3DXVECTOR3(m_spriteSpec->getWidth() / 2,
		m_spriteSpec->getHeight() / 2, 0);

	D3DXVECTOR3 renderPosition = D3DXVECTOR3(m_position.x, m_position.y, 0);
	//renderPosition = renderPosition + D3DXVECTOR3(this->m_parent->getOffsetToScene().x, this->m_parent->getOffsetToScene().y, 0);

	renderPosition = ViewPort::getInstance()->transform(renderPosition);

	// vẽ.
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);// (D3DXSPRITE_ALPHABLEND);

	spriteHandler->Draw(m_texture->getTexture(), &srcRect, &centerOfSpriteTexture, &renderPosition, D3DCOLOR_XRGB(255,255,255));
	spriteHandler->End();

	Node::render();
}

//void GameObject::setRenderPosition(D3DXVECTOR3 position)
//{
//	m_renderPosition = position;
//}
//
//SpriteSpec* GameObject::getCurrentSpriteSpec()
//{
//	return *m_index;
//}
//
//
////void GameObject::update()
////{
////	nextFrame(); // thiết lập lại index thành frame tiếp theo.
////
////}
//
//void GameObject::setup()
//{
//	
//	m_listFramePerAnimtion = Animation::getInstance()->getListSprteOfAnimation(m_Sprite, m_state);
//	m_index = m_listFramePerAnimtion.begin();
//}
//
//void GameObject::nextFrame()
//{
//	if (m_index != m_listFramePerAnimtion.end())
//		m_index++;
//	else
//		m_index = m_listFramePerAnimtion.begin();
//}
//
//EState GameObject::getState()
//{
//	return m_state;
//}
//void GameObject::setState(EState state)
//{
//	m_state = state;
//}
//
//ESprite GameObject::getSprite()
//{
//	return m_Sprite;
//}

void GameObject::update(long delta)
{

}

void GameObject::onKeyUp(int keyCode){

}

void GameObject::onKeyDown(int keyCode){

}

void GameObject::processKeyState(BYTE *keyState){

}

FPOINT GameObject::getVelocity(){
	return this->m_velocity;
}

void GameObject::setVelocity(FPOINT velocity){
	this->m_velocity = velocity;
}