#include "MegaMan.h"
#include "../../SFramework/SpriteAndAnimation/AnimationManager.h"
#include "../../SFramework/GameTime.h"
#include <dinput.h>

MegaMan::MegaMan() : GameObject()
{
	GameObject::setType(10);
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
	// việc tính vị trí sẽ vẽ ở thời điểm tiếp theo được tính trong hàm onCollide trong vài trường hợp đặc biệt
	
	if (this->getSkipUpdatePosition()){
		this->setSkipUpdatePosition(false);
	}
	else{
		FPOINT currentPosition = this->getPosition();
		DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
		FPOINT velocity = this->getVelocity();
		velocity.x += this->getAcceleration().x*deltaTime;
		velocity.y += this->getAcceleration().y*deltaTime;
		currentPosition.x = currentPosition.x + velocity.x*deltaTime;
		currentPosition.y = currentPosition.y + velocity.y*deltaTime;
		this->setPostion(currentPosition);

	}

	// set position to render
	GameObject::render();

	resetVelocityAndAcceleration();
}

void MegaMan::processInput(LPDIRECT3DDEVICE9 d3ddv, int Delta){

}

void MegaMan::onKeyDown(int keyCode){
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
	FPOINT velocity = this->getVelocity();
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	velocity.x += this->getAcceleration().x*deltaTime;
	velocity.y += this->getAcceleration().y*deltaTime;
	this->setVelocity(velocity);
	this->setAcceleration(FPOINT(MEGA_MAN_ACCELERATION_X, GRAVITATIONAL_ACCELERATION));
}

void MegaMan::onCollision(GameObject* staticObject){
	GameState* newState = m_state->onCollision(this, staticObject);
	if (newState != NULL){
		delete m_state;
		m_state = newState;
		m_state->enter(this);
	}
}
