#include "MegaMan.h"
#include "../../SFramework/SpriteAndAnimation/AnimationManager.h"
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
	SpriteSpec* currentSpriteSpec = m_animation->getCurrentSpriteSpec();
	GameObject::setSpriteSpec(currentSpriteSpec);

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

	resetVelocityAndAcceleration();
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
	//FPOINT currentPosition = this->getPosition();
	//DWORD deltaTime = GameTime::getInstance()->getDeltaTime();

	//// key right và left thì vy = 0
	//if (keyCode == DIK_RIGHT)
	//{

	//	/*currentPosition.x = currentPosition.x + getVelocity().x*deltaTime;
	//	this->setPostion(currentPosition);
	//	trace("deta time " + std::to_string(deltaTime));*/
	//}
	//else
	//if (keyCode == DIK_LEFT)
	//{
	//	/*currentPosition.x = currentPosition.x - getVelocity().x*deltaTime;
	//	this->setPostion(currentPosition);*/
	//	//trace("left button");

	//}
	//else if (keyCode == DIK_SPACE)
	//{
	//	trace("space button");

	//}
	GameState* state = m_state->onKeyDown(this, keyCode);
	if (state != NULL){
		delete m_state;
		m_state = state;
		m_state->enter(this);
	}
}
void MegaMan::onKeyUp(int KeyCode){
	GameState* state = m_state->onKeyUp(this, KeyCode);
	if (state != NULL){
		delete m_state;
		m_state = state;
		m_state->enter(this);
	}
}

void MegaMan::changeAnimation(int character, int state){
	m_animation = AnimationManager::getInstance()->getAnimationSprites(character, state);
	GameObject::setSpriteSpec(m_animation->getCurrentSpriteSpec());
}

void MegaMan::processKeyState(BYTE *keyState){
	GameState* state = m_state->processKeyState(this, keyState);
	if (state != NULL){
		delete m_state;
		m_state = state;
		m_state->enter(this);
	}
	//FPOINT currentPosition = this->getPosition();
	//DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	//if ((keyState[DIK_RIGHT] & 0x80) > 0)
	//{
	//	FPOINT velocity = this->getVelocity();
	//	/*if (velocity.x < 0.0f)
	//		velocity.x *= -1;
	//		else if (velocity.x == 0.0f)*/
	//	velocity.x = MEGA_MAN_VELOCITY_X;
	//	this->setVelocity(velocity);
	//}
	//else
	//if ((keyState[DIK_LEFT] & 0x80) > 0)
	//{
	//	FPOINT velocity = this->getVelocity();
	//	/*	if (velocity.x > 0.0f)
	//			velocity.x *= -1;
	//			else if (velocity.x == 0.0f)*/
	//	velocity.x = -MEGA_MAN_VELOCITY_X;
	//	this->setVelocity(velocity);
	//}

}

void MegaMan::resetVelocityAndAcceleration(){
	// reset velocity
	//this->setVelocity(FPOINT(0, 0));
	this->setAcceleration(FPOINT(MEGA_MAN_ACCELERATION_X, GRAVITATIONAL_ACCELERATION));
}

void MegaMan::onCollision(GameObject* staticObject){
	GameState* newState = m_state->onCollision(this, staticObject);
	if (newState != NULL){
		delete m_state;
		m_state = newState;
		m_state->enter(this);
	}
	/*SpriteSpec* currentSpriteSpec = m_animation->getCurrentSpriteSpec();
	GameObject::setSpriteSpec(currentSpriteSpec);*/
	//SpriteSpec* currentSpriteSpec = GameObject::getSpriteSpec();

	//int staticObjectType = staticObject->getType();
	//DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	//FPOINT velocity = this->getVelocity();
	//velocity.x += this->getAcceleration().x*deltaTime;
	//velocity.y += this->getAcceleration().y*deltaTime;
	//
	//D3DXVECTOR2 normal;

	//// set Collision BOX for mega man. 
	//BOX collisionBox(this->getPosition().x, this->getPosition().y, this->getSpriteSpec()->getWidth(),
	//	this->getSpriteSpec()->getHeight(), velocity.x * deltaTime, velocity.y*deltaTime);
	//this->setCollisionBox(collisionBox);

	//// collision
	//float collisionTime = Collision::CheckCollision(this, staticObject, normal);
	//if (collisionTime > 0.0f && collisionTime < 1.0f){
	//	int a = 5;
	//	/*
	//	NOTE : Khi xét va chạm, không set vị trí và chạm giữa 2 vật trùng nhau mà phải cho chúng nó lệch nhau ít nhất 1px. 
	//	- Position ở đây là top-left của vật. 
	//	*/
	//	//vật đi từ trên xuống
	//	if (normal.x == 0.0f && normal.y == 1.0f)
	//	{
	//		FPOINT newPosition = this->getPosition();
	//		newPosition.y = currentSpriteSpec->getHeight() + staticObject->getCollisionBox().y + 1;
	//		this->setPostion(newPosition);
	//		/*
	//			Khi mega man đứng trên mặt đất, có phản lực N triệt tiêu lực hấp dẫn. Do đó có thể coi
	//			gia tốc trọng từng = 0 và v.y = 0;
	//		*/ 
	//		this->setAcceleration(FPOINT(MEGA_MAN_ACCELERATION_X, 0.0f)); 
	//		this->setVelocity(FPOINT(this->getVelocity().x, 0.0f));
	//	}
	//	// vật đi từ trái sang
	//	else if (normal.x == -1.0f && normal.y == 0.0f){
	//		FPOINT newPosition = this->getPosition();
	//		newPosition.x = -currentSpriteSpec->getWidth() + staticObject->getCollisionBox().x -1;
	//		this->setPostion(newPosition);
	//		
	//		this->setVelocity(FPOINT(-this->getVelocity().x, 0.0f));
	//	}
	//	// vật đi từ phải sang
	//	else if (normal.x == 1.0f && normal.y == 0.0f){
	//		FPOINT newPosition = this->getPosition();
	//		newPosition.x = staticObject->getCollisionBox().width + staticObject->getCollisionBox().x + 1;
	//		this->setPostion(newPosition);

	//		//this->setAcceleration(FPOINT(MEGA_MAN_ACCELERATION_X, GRAVITATIONAL_ACCELERATION));
	//		// vì chúng ta ko sử dụng gia tốc trục x nên khi va chạm trái phải, ta không set lại gia tốc
	//		// gia tốc trục y sẽ được giữ của lần xét va chạm trước đó. 
	//		this->setVelocity(FPOINT(-this->getVelocity().x, 0.0f));
	//	}

	//}

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