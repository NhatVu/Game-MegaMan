#include "Suzy.h"
#include "../../SFramework/SFramework.h"

Suzy::Suzy()
{
	this->countFrame = 0;
	this->setAcceleration(FPOINT(0.0f, 0.0f));
}


Suzy::~Suzy()
{
}

void Suzy::render() {
	if (this->getState() == EState::IDLE)
		this->countFrame++;
	if (this->countFrame == 5){
		this->setStopUpdateAnimation(true);
		GameObject::setSpriteSpec(m_animation->getSpriteSpecs()[1]);

	}
	if (this->countFrame == 3 * FPS)
	{
		this->countFrame = 0;
		this->setState(EState::ACTIVE);
		this->setStopUpdateAnimation(0);
		if (this->getDirection() == 1){
			if (this->leftToRight == 1) // suzy va chạm từ trái sang lần trước đó
			this->setVelocity(FPOINT(-SUZY_VELOCITY, 0.0f));
			else this->setVelocity(FPOINT(SUZY_VELOCITY, 0.0f));
		}
		else {
			if (this->topToBottom == 1)
			this->setVelocity(FPOINT(0.0f, -SUZY_VELOCITY));
			else this->setVelocity(FPOINT(0.0f, SUZY_VELOCITY));
		}
	}
	if (this->getStopUpdateAnimation() == 0){
		SpriteSpec* currentSpriteSpec = m_animation->getCurrentSpriteSpec();
		GameObject::setSpriteSpec(currentSpriteSpec);
	}
	// set position to render
	GameObject::render();
}

void Suzy::onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector){
	if (staticObject->getCollisionBox().x == 133){
		int a = 5;
	}
	if (collisionTime > 0.0f && collisionTime <= 1.0f){
		if (staticObject->getType() == ECharacter::MEGAMAN_BULLET){
			this->die();
			return;
		}

		if (staticObject->getType() == ECharacter::STATIC){
			FPOINT velocity = this->getVelocity();
			velocity.x *= -0;
			velocity.y *= -0;
			this->setVelocity(velocity);
			this->setState(EState::IDLE);
			//vật đi từ trên xuống
			if (collisionVector.x == 0.0f && collisionVector.y == 1.0f)
			{
				this->topToBottom = 1;
			}
			// vật đi chuyển từ dưới lên
			else if (collisionVector.x == 0.0f && collisionVector.y == -1.0f)
			{
				this->topToBottom = -1;
			}
			// vật đi từ phải sang
			else if (collisionVector.x == 1.0f && collisionVector.y == 0.0f){
				this->leftToRight = -1;
			}
			else
				// vật đi từ trái sang
			if (collisionVector.x == -1.0f && collisionVector.y == 0.0f){
				this->leftToRight = 1;
			}
		}
	}

}
void Suzy::updatePosition(){
	if (this->getIsInactive())
		return;
	FPOINT currentPosition = this->getPosition();
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	FPOINT velocity = this->getVelocity();
	velocity.x += this->getAcceleration().x*deltaTime;
	velocity.y += this->getAcceleration().y*deltaTime;
	currentPosition.x = currentPosition.x + velocity.x*deltaTime;
	currentPosition.y = currentPosition.y + velocity.y*deltaTime;

	//velocity.x = KAMADOMA_VELOCITY_X;
	this->setPostion(currentPosition);
	this->setVelocity(velocity);
	this->setAcceleration(FPOINT(0.0f, 0.0f));
}
void Suzy::calculateCollisionBox(){
	if (this->getIsInactive())
		return;
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	FPOINT velocity = this->getVelocity();

	velocity.x += this->getAcceleration().x*deltaTime;
	velocity.y += this->getAcceleration().y*deltaTime;

	// set Collision BOX for kamadoma. 
	BOX collisionBox(this->getPosition().x, this->getPosition().y, SUZY_VIRTUAL_WIDTH,
		SUZY_VIRTUAL_HEIGHT, velocity.x * deltaTime, velocity.y*deltaTime);
	this->setCollisionBox(collisionBox);
}
void Suzy::setState(int state){
	GameObject::setState(state);
	m_animation = AnimationManager::getInstance()->getAnimationSprites(ECharacter::SUZY, state);
	GameObject::setSpriteSpec(m_animation->getSpriteSpecs()[0]);
}

void Suzy::resetToInit(){
	this->setPostion(this->getInitPosition());
	BOX oldCollisionBox = this->getCollisionBox();
	oldCollisionBox.x = this->getPosition().x;
	oldCollisionBox.y = this->getPosition().y;
	oldCollisionBox.width = SUZY_VIRTUAL_WIDTH;
	oldCollisionBox.height = SUZY_VIRTUAL_HEIGHT;
	oldCollisionBox.vx = 0.0f;
	oldCollisionBox.vy = 0.0f;
	this->setCollisionBox(oldCollisionBox);

	this->setState(EState::ACTIVE);
}
void Suzy::die(){
	this->setState(EState::DIE);
	this->setIsInactive(true);
	//this->setPostion(this->getInitPosition());
	BOX oldCollisionBox = this->getCollisionBox();
	oldCollisionBox.x = this->getInitPosition().x;
	oldCollisionBox.y = this->getInitPosition().y;
	oldCollisionBox.width = SUZY_VIRTUAL_WIDTH;
	oldCollisionBox.height = SUZY_VIRTUAL_HEIGHT;
	oldCollisionBox.vx = 0.0f;
	oldCollisionBox.vy = 0.0f;
	this->setCollisionBox(oldCollisionBox);
	this->setVelocity(FPOINT(0.0f, 0.0f));
	this->setAcceleration(FPOINT(0.0f, 0.0f));
}