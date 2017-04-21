#include "GameObject.h"
#include "SFramework.h"
#include "Director.h"
#include "SpriteAndAnimation/Texture.h"
#include "Camera/ViewPort.h"
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

	if (m_spriteSpec->getHeight() == 24.0f){
		int a = 5;
	}
	
	// tâm của frame. tọa độ top = 0. left = 0
	D3DXVECTOR3 centerOfSpriteTexture = D3DXVECTOR3(m_spriteSpec->getWidth() / 2,
		m_spriteSpec->getHeight() / 2, 0);

	D3DXVECTOR3 renderPosition = D3DXVECTOR3(m_position.x + m_spriteSpec->getWidth() / 2, m_position.y - m_spriteSpec->getHeight() / 2, 0);
	renderPosition = ViewPort::getInstance()->worldToViewport(renderPosition);
	FPOINT vp = ViewPort::getInstance()->getPosition();
	//D3DXMATRIX matFinal;
	//D3DXVECTOR2 inScale = D3DXVECTOR2(1, 1); // flip object 
	//D3DXVECTOR2 inRotationCenter = D3DXVECTOR2(1, 1);
	//D3DXVECTOR2 scalingScenter = D3DXVECTOR2(1,1);
	//D3DXVECTOR2 position = D3DXVECTOR2(renderPosition.x, renderPosition.y);
	//float inRotation = D3DXToRadian(0.0f);

	//D3DXMatrixTransformation2D(&matFinal, &scalingScenter, 0, &inScale, &inRotationCenter,
	//	inRotation, &position);
	D3DXMATRIX mt1;
	D3DXMatrixScaling(&mt1, 1, 1, 0); //scale object
	D3DXMATRIX output;
	D3DXMATRIX t1, t2, r;
	D3DXMatrixTranslation(&t1, -50, -250, 0);
	D3DXMatrixRotationY(&r, D3DXToRadian(180.0f));
	D3DXMatrixTranslation(&t2, 50, 250, 0);

	/*D3DXMatrixMultiply(&output, &mt1,&t1);
	D3DXMatrixMultiply(&output, &output, &r);
	D3DXMatrixMultiply(&output, &output, &t2);*/

	D3DXMatrixTransformation(&output, NULL, NULL, &D3DXVECTOR3(2, 2, 0), NULL, NULL, NULL);


	// vẽ.
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);// (D3DXSPRITE_ALPHABLEND);
	spriteHandler->SetTransform(&output);
	//spriteHandler->Draw(m_texture->getTexture(), &srcRect, &centerOfSpriteTexture, &renderPosition, D3DCOLOR_XRGB(255,255,255));
	spriteHandler->Draw(m_texture->getTexture(), &srcRect, &centerOfSpriteTexture, &renderPosition, D3DCOLOR_XRGB(255, 255, 255));
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

BOX GameObject::getCollisionBox(){
	return this->m_collisionBox;
}

void GameObject::setCollisionBox(BOX box){
	this->m_collisionBox = box;
}

void GameObject::onCollision(GameObject* staticObject){}