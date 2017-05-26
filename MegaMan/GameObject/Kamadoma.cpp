#include "Kamadoma.h"
#include "../../SFramework/Map/ObjectManager.h"

Kamadoma::Kamadoma()
{
	GameObject::setAcceleration(FPOINT(0, GRAVITATIONAL_ACCELERATION / 2));
	setVelocity(FPOINT(-KAMADOMA_VELOCITY_X, KAMADOMA_VELOCITY_Y));
	canAttack = true;
}


Kamadoma::~Kamadoma()
{
}

void Kamadoma::setState(int state){
	//this->state = state;
	GameObject::setState(state);
	m_animation = AnimationManager::getInstance()->getAnimationSprites(ECharacter::KAMADOMA, state);
	GameObject::setSpriteSpec(m_animation->getSpriteSpecs()[0]);
}
void Kamadoma::render() {
	SpriteSpec* currentSpriteSpec = m_animation->getCurrentSpriteSpec();
	GameObject::setSpriteSpec(currentSpriteSpec);
	// set position to render
	GameObject::render();
}

void Kamadoma::calculateCollisionBox(){
	if (this->getIsInactive())
		return;
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	FPOINT velocity = this->getVelocity();

	velocity.x += this->getAcceleration().x*deltaTime;
	velocity.y += this->getAcceleration().y*deltaTime;

	// set Collision BOX for kamadoma. 
	BOX collisionBox(this->getPosition().x, this->getPosition().y, KAMADOMA_VIRTUAL_WIDTH,
		KAMADOMA_VIRTUAL_HEIGHT, velocity.x * deltaTime, velocity.y*deltaTime);
	this->setCollisionBox(collisionBox);
}

void Kamadoma::die(){
	this->setState(EState::DIE);
	this->setIsInactive(true);
	//this->setPostion(this->getInitPosition());
	BOX oldCollisionBox = this->getCollisionBox();
	oldCollisionBox.x = this->getInitPosition().x;
	oldCollisionBox.y = this->getInitPosition().y;
	oldCollisionBox.width = KAMADOMA_VIRTUAL_WIDTH;
	oldCollisionBox.height = KAMADOMA_VIRTUAL_HEIGHT;
	oldCollisionBox.vx = 0.0f;
	oldCollisionBox.vy = 0.0f;
	this->setCollisionBox(oldCollisionBox);
	this->setVelocity(FPOINT(0.0f, 0.0f));
	this->setAcceleration(FPOINT(0.0f, 0.0f));

}
void Kamadoma::onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector){
	SpriteSpec* currentSpriteSpec = this->getSpriteSpec();

	int staticObjectType = staticObject->getType();
	D3DXVECTOR2 normal = collisionVector;
	
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	FPOINT velocity = this->getVelocity();
	//
	//velocity.x += this->getAcceleration().x*deltaTime;
	//velocity.y += this->getAcceleration().y*deltaTime;

	//// set Collision BOX for kamadoma. 
	//BOX collisionBox(this->getPosition().x, this->getPosition().y, KAMADOMA_VIRTUAL_WIDTH,
	//	KAMADOMA_VIRTUAL_HEIGHT, velocity.x * deltaTime, velocity.y*deltaTime);
	//this->setCollisionBox(collisionBox);

	// collision
	BOX collisionBox = this->getCollisionBox();
	//float collisionTime = Collision::CheckCollision(this, staticObject, normal);
	if (collisionTime > 0.0f && collisionTime < 1.0f){
		if (staticObjectType == ECharacter::MEGAMAN_BULLET){
			this->die();
			return;
		}
		/*
		NOTE : Khi xét va chạm, không set vị trí và chạm giữa 2 vật trùng nhau mà phải cho chúng nó lệch nhau ít nhất 1px.
		- Position ở đây là top-left của vật.
		*/
		//vật đi từ trên xuống
		FPOINT newPosition = this->getPosition();
		//FPOINT kamadomaPos = this->getPosition();
		FPOINT megaManPos = ObjectManager::getInstance()->getMegaMan()->getPosition();
		if (staticObjectType == ECharacter::MEGAMAN){
			int a = 5;
		}
		if (normal.x == 0.0f && normal.y == 1.0f)
		{
			switch (staticObjectType)
			{
			case ECharacter::STATIC:
				velocity.y = KAMADOMA_VELOCITY_Y;
				
				newPosition.y = collisionBox.height + staticObject->getCollisionBox().y + 1;
				// xác định hướng đi của kamadoma dựa vào vị trí của mega man

				if (megaManPos.x - newPosition.x >= KAMADOMA_FORCE_ATTACK_DISTANCE){
					velocity.x = KAMADOMA_VELOCITY_X;
					canAttack = true;
				}
				else if (newPosition.x - megaManPos.x >= KAMADOMA_FORCE_ATTACK_DISTANCE){
					velocity.x = -KAMADOMA_VELOCITY_X;
					canAttack = true;
				}
				else if (canAttack){
					int numberFrame = (KAMADOMA_VELOCITY_Y / (-GRAVITATIONAL_ACCELERATION/2 * deltaTime)) * 2 ;
					velocity.x = (megaManPos.x - newPosition.x) / (deltaTime * numberFrame);
					canAttack = false;
				}else

				if (isRightCollision){// đi từ phải sang
					velocity.x = 1.5f*KAMADOMA_VELOCITY_X;
				}
				else velocity.x = -1.5f*KAMADOMA_VELOCITY_X;

				isRightCollision = false;
				isLeftCollision = false;
				this->setPostion(newPosition);
				this->setVelocity(velocity);

				break;
			default:
				break;
			}
		}
		// vật đi chuyển từ dưới lên
		else if (normal.x == 0.0f && normal.y == -1.0f)
		{
		}
		// vật đi từ phải sang
		else if (normal.x == 1.0f && normal.y == 0.0f){
			switch (staticObjectType)
			{
			case ECharacter::STATIC:
				velocity.x = 0;
				isRightCollision = true;
				newPosition.x = staticObject->getCollisionBox().width + staticObject->getCollisionBox().x + 1;
				//newPosition.y = staticObject->getCollisionBox().y - staticObject->getCollisionBox().height + collisionBox.height + 1;
				this->setPostion(newPosition);
				this->setVelocity(velocity);
				break;
			default:
				break;
			}
		}
		else
			// vật đi từ trái sang
		if (normal.x == -1.0f && normal.y == 0.0f){
			switch (staticObjectType)
			{
			case ECharacter::STATIC:
				velocity.x *= 0;
				isLeftCollision = true;
				newPosition.x = staticObject->getCollisionBox().x - collisionBox.width - 1;
				//newPosition.y = staticObject->getCollisionBox().y - staticObject->getCollisionBox().height + collisionBox.height + 1;
				this->setPostion(newPosition);
				this->setVelocity(velocity);
				break;
			default:
				break;
			}
		}
	}
}
void Kamadoma::updatePosition(){
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
	this->setAcceleration(FPOINT(0.0f, GRAVITATIONAL_ACCELERATION / 2));
}

void Kamadoma::resetToInit(){
	GameObject::setAcceleration(FPOINT(0, GRAVITATIONAL_ACCELERATION / 2));

	this->setPostion(this->getInitPosition());
	BOX oldCollisionBox = this->getCollisionBox();
	oldCollisionBox.x = this->getPosition().x;
	oldCollisionBox.y = this->getPosition().y;
	oldCollisionBox.width = KAMADOMA_VIRTUAL_WIDTH;
	oldCollisionBox.height = KAMADOMA_VIRTUAL_HEIGHT;
	oldCollisionBox.vx = 0.0f;
	oldCollisionBox.vy = 0.0f;
	this->setCollisionBox(oldCollisionBox);

	this->setState(EState::ACTIVE);

}