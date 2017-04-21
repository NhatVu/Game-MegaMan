#include "MegaMan.h"
#include "../../SFramework/ResourceManager.h"
#include "../../SFramework/GameTime.h"
#include <dinput.h>

MegaMan::MegaMan() : GameObject()
{
	GameObject::setAcceleration(FPOINT(0, GRAVITATIONAL_ACCELERATION));
	//GameObject::setVelocity(FPOINT(MEGA_MAN_VELOCITY_X, 0.0f));

}


MegaMan::~MegaMan()
{
}

void MegaMan::setTexture(Texture* texture){
	GameObject::setTexture(texture);
}
void MegaMan::render(){
	
	// calculate possition to render
	// việc tính vị trí sẽ vẽ ở thời điểm tiếp theo được tính trong hàm onCollide
	FPOINT currentPosition = this->getPosition();
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	FPOINT velocity = this->getVelocity();
	velocity.x += this->getAcceleration().x*deltaTime;
	velocity.y += this->getAcceleration().y*deltaTime;
	currentPosition.x = currentPosition.x + velocity.x*deltaTime;
	currentPosition.y = currentPosition.y + velocity.y*deltaTime;

	// set position to render
	this->setPostion(currentPosition);
	GameObject::render();

	//resetVelocityAndAcceleration();
}

void MegaMan::processInput(LPDIRECT3DDEVICE9 d3ddv, int Delta){
	/*if (isKeyDown(DIK_RIGHT))
	{
	MessageBox(NULL, L"right", NULL, NULL);
	}
	else
	if (isKeyDown(DIK_LEFT))
	{
	MessageBox(NULL, L"left", NULL, NULL);

	}
	else if (isKeyDown(DIK_SPACE))
	{
	MessageBox(NULL, L"Space", NULL, NULL);

	}*/
}

void MegaMan::onKeyDown(int keyCode){
	FPOINT currentPosition = this->getPosition();
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();

	// key right và left thì vy = 0
	if (keyCode == DIK_RIGHT)
	{

		/*currentPosition.x = currentPosition.x + getVelocity().x*deltaTime;
		this->setPostion(currentPosition);
		trace("deta time " + std::to_string(deltaTime));*/
	}
	else
	if (keyCode == DIK_LEFT)
	{
		/*currentPosition.x = currentPosition.x - getVelocity().x*deltaTime;
		this->setPostion(currentPosition);*/
		//trace("left button");

	}
	else if (keyCode == DIK_SPACE)
	{
		trace("space button");

	}
}
void MegaMan::onKeyUp(int KeyCode){}

void MegaMan::changeAnimation(int character, int state){
	m_animation = ResourceManager::getInstance()->getAnimationSprites(character, state);
	GameObject::setSpriteSpec(m_animation->getCurrentSpriteSpec());
}

void MegaMan::processKeyState(BYTE *keyState){
	FPOINT currentPosition = this->getPosition();
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	if ((keyState[DIK_RIGHT] & 0x80) > 0)
	{
		FPOINT velocity = this->getVelocity();
		/*if (velocity.x < 0.0f)
			velocity.x *= -1;
			else if (velocity.x == 0.0f)*/
		velocity.x = MEGA_MAN_VELOCITY_X;
		this->setVelocity(velocity);
	}
	else
	if ((keyState[DIK_LEFT] & 0x80) > 0)
	{
		FPOINT velocity = this->getVelocity();
		/*	if (velocity.x > 0.0f)
				velocity.x *= -1;
				else if (velocity.x == 0.0f)*/
		velocity.x = -MEGA_MAN_VELOCITY_X;
		this->setVelocity(velocity);
	}

}

void MegaMan::resetVelocityAndAcceleration(){
	// reset velocity
	this->setVelocity(FPOINT(0, 0));
	this->setAcceleration(FPOINT(MEGA_MAN_ACCELERATION_X, GRAVITATIONAL_ACCELERATION));
}

void MegaMan::onCollision(GameObject* staticObject){
	SpriteSpec* currentSpriteSpec = m_animation->getCurrentSpriteSpec();
	GameObject::setSpriteSpec(currentSpriteSpec);

	int staticObjectType = staticObject->getType();
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	FPOINT velocity = this->getVelocity();
	velocity.x += this->getAcceleration().x*deltaTime;
	velocity.y += this->getAcceleration().y*deltaTime;
	
	D3DXVECTOR2 normal;

	// set Collision BOX for mega man. 
	BOX collisionBox(this->getPosition().x, this->getPosition().y, this->getSpriteSpec()->getWidth(),
		this->getSpriteSpec()->getHeight(), velocity.x * deltaTime, velocity.y*deltaTime);
	this->setCollisionBox(collisionBox);

	// collision
	float collisionTime = Collision::CheckCollision(this, staticObject, normal);
	if (collisionTime > 0.0f && collisionTime < 1.0f){
		int a = 5;
		//if (normal.x == 0.0f && normal.y == 1.0f)
		//{
		//	FPOINT newPosition = this->getPosition();
		//	newPosition.y = currentSpriteSpec->getHeight() + staticObject->getCollisionBox().y;
		//	this->setPostion(newPosition);
		//	/*
		//		Khi mega man đứng trên mặt đất, có phản lực N triệt tiêu lực hấp dẫn. Do đó có thể coi
		//		gia tốc trọng từng = 0 và v.y = 0;
		//	*/
		//	this->setAcceleration(FPOINT(MEGA_MAN_ACCELERATION_X, 0.0f)); 
		//	this->setVelocity(FPOINT(this->getVelocity().x, 0.0f));
		//}
	}

}
//void MegaMan::updateKeyboard(int keyCode){
//	if (keyCode == DIK_RIGHT)
//	{
//	MessageBox(NULL, L"right", NULL, NULL);
//	}
//	else
//	if (keyCode == DIK_LEFT)
//	{
//	MessageBox(NULL, L"left", NULL, NULL);
//
//	}
//	else if (keyCode == DIK_SPACE)
//	{
//	MessageBox(NULL, L"Space", NULL, NULL);
//
//	}
//}