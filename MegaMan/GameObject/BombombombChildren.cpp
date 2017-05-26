#include "BombombombChildren.h"

BombombombChildren::BombombombChildren()
{
	setIsInactive(false);
}


BombombombChildren::~BombombombChildren()
{
}

void BombombombChildren::render() {
	SpriteSpec* currentSpriteSpec = m_animation->getCurrentSpriteSpec();
	GameObject::setSpriteSpec(currentSpriteSpec);
	// set position to render
	GameObject::render();
}

void BombombombChildren::onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector){
	if (collisionTime > 0.0f && collisionTime < 1.0f){
		int staticObjectType = staticObject->getType();
		if (staticObjectType == ECharacter::STATIC){
			this->die();
		}
		/*else if (staticObjectType == ECharacter::MEGAMAN){

		}*/
	}
}
void BombombombChildren::updatePosition(){
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
void BombombombChildren::calculateCollisionBox(){
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
void BombombombChildren::setState(int state){
	GameObject::setState(state);
	m_animation = AnimationManager::getInstance()->getAnimationSprites(ECharacter::BOMBOMBOM_CHILDREN, state);
	GameObject::setSpriteSpec(m_animation->getSpriteSpecs()[0]);
}

void BombombombChildren::resetToInit(){
	this->setPostion(this->getInitPosition());
	BOX oldCollisionBox = this->getCollisionBox();
	oldCollisionBox.x = this->getPosition().x;
	oldCollisionBox.y = this->getPosition().y;
	oldCollisionBox.width = this->getSpriteSpec()->getWidth();
	oldCollisionBox.height = this->getSpriteSpec()->getHeight();
	oldCollisionBox.vx = 0.0f;
	oldCollisionBox.vy = 0.0f;
	this->setCollisionBox(oldCollisionBox);

	this->setState(EState::ACTIVE);
	this->setAcceleration(FPOINT(0.0f, GRAVITATIONAL_ACCELERATION / 5));
	this->setVelocity(FPOINT(this->getVelocity().x, BOMBOMBOMB_CHILDREN_VELOCITY_Y));

}
void BombombombChildren::die(){
	this->setState(EState::DIE);
	this->setIsInactive(true);
	BOX oldCollisionBox = this->getCollisionBox();
	oldCollisionBox.x = this->getInitPosition().x;
	oldCollisionBox.y = this->getInitPosition().y;
	oldCollisionBox.width = this->getSpriteSpec()->getWidth();
	oldCollisionBox.height = this->getSpriteSpec()->getHeight();
	oldCollisionBox.vx = 0.0f;
	oldCollisionBox.vy = 0.0f;
	this->setCollisionBox(oldCollisionBox);


}