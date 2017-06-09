#include "SuperCutter.h"


SuperCutter::SuperCutter()
{
	this->setAcceleration(FPOINT(0.0f, GRAVITATIONAL_ACCELERATION/2));
	this->setAttackDamage(4);
}


SuperCutter::~SuperCutter()
{
}

void SuperCutter::render() {
	SpriteSpec* currentSpriteSpec = m_animation->getCurrentSpriteSpec();
	GameObject::setSpriteSpec(currentSpriteSpec);
	// set position to render
	GameObject::render();
}

void SuperCutter::onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector){}

void SuperCutter::updatePosition(){
	if (this->getIsInactive()) // cho trường hợp vừa die xong, nó sẽ chạy qua hàm updatePosition
		return;
	FPOINT currentPosition = this->getPosition();
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	FPOINT velocity = this->getVelocity();
	velocity.x += this->getAcceleration().x*deltaTime;
	velocity.y += this->getAcceleration().y*deltaTime;
	currentPosition.x = currentPosition.x + velocity.x*deltaTime;
	currentPosition.y = currentPosition.y + velocity.y*deltaTime;

	this->setPostion(currentPosition);
	this->setVelocity(velocity);
}

void SuperCutter::calculateCollisionBox(){
	if (this->getIsInactive())
		return;
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	FPOINT velocity = this->getVelocity();

	velocity.x += this->getAcceleration().x*deltaTime;
	velocity.y += this->getAcceleration().y*deltaTime;

	// set Collision BOX for kamadoma. 
	BOX collisionBox(this->getPosition().x, this->getPosition().y, this->getSpriteSpec()->getWidth(),
		this->getSpriteSpec()->getHeight(), velocity.x * deltaTime, velocity.y*deltaTime);
	this->setCollisionBox(collisionBox);
}

void SuperCutter::setState(int state){
	GameObject::setState(state);
	m_animation = AnimationManager::getInstance()->getAnimationSprites(ECharacter::SUPER_CUTTER, state);
	GameObject::setSpriteSpec(m_animation->getSpriteSpecs()[0]);
}

void SuperCutter::resetToInit(){}