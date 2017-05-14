#include "GameObject.h"
#include "SFramework.h"
#include "Director.h"
#include "SpriteAndAnimation/Texture.h"
#include "Camera/ViewPort.h"
#include "Trace.h"

using namespace s_framework;

GameObject::GameObject()
{
	mFlipVertical = true;
	stopUpdateAnimation = false;
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
	srcRect.top = m_spriteSpec->getY();
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


	D3DXMATRIX matFinal;
	D3DXVECTOR2 inScale = D3DXVECTOR2(mFlipVertical, 1); // flip object 
	//D3DXVECTOR2 inRotationCenter = D3DXVECTOR2(renderPosition.x, renderPosition.y);
	D3DXVECTOR2 scalingScenter = D3DXVECTOR2(1,1 ); // scale vật ngay tại tâm.
	D3DXVECTOR2 position = D3DXVECTOR2(renderPosition.x, renderPosition.y);
	//float inRotation = D3DXToRadian(0.0f);


	D3DXMatrixTransformation2D(&matFinal, &scalingScenter, 0, &inScale, NULL,
		NULL, &position);
	// vẽ.
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);// (D3DXSPRITE_ALPHABLEND);
	spriteHandler->SetTransform(&matFinal);
	spriteHandler->Draw(m_texture->getTexture(), &srcRect, &centerOfSpriteTexture, NULL, D3DCOLOR_XRGB(255, 255, 255));
	spriteHandler->End();

	Node::render();
}

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

void GameObject::updatePosition(){}