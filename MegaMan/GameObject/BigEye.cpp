#include "BigEye.h"
#include "../../SFramework/Map/ObjectManager.h"


BigEye::BigEye()
{
	GameObject::setAcceleration(FPOINT(0, GRAVITATIONAL_ACCELERATION / 2));
	setVelocity(FPOINT(-BIG_EYE_VELOCITY_X, BIG_EYE_VELOCITY_Y));
	this->setAttackDamage(10);
	this->setBlood(20);
}


BigEye::~BigEye()
{
}

void BigEye::render() {

	SpriteSpec* currentSpriteSpec = m_animation->getCurrentSpriteSpec();
	GameObject::setSpriteSpec(currentSpriteSpec);
	// set position to render
	GameObject::render();
}

void BigEye::onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector){
	int staticObjectType = staticObject->getType();
	D3DXVECTOR2 normal = collisionVector;

	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	FPOINT velocity = this->getVelocity();
	// collision
	BOX collisionBox = this->getCollisionBox();
	//float collisionTime = Collision::CheckCollision(this, staticObject, normal);
	if (collisionTime > 0.0f && collisionTime <= 1.0f){
		if (staticObjectType == ECharacter::MEGAMAN_BULLET && staticObject->getType() != EState::DIE){
			int blood = this->getBlood();
			int staticAttackDamage = staticObject->getAttackDamage();
			blood -= staticAttackDamage;
			if (blood <= 0){
				this->die();
				return;
			}
			else this->setBlood(blood);
		}

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
				velocity.y = BIG_EYE_VELOCITY_Y;
				if (megaManPos.x - newPosition.x >0){
					velocity.x = BIG_EYE_VELOCITY_X;
					this->setFlipVertical(-1);
				}
				else{
					velocity.x = -BIG_EYE_VELOCITY_X;
					this->setFlipVertical(1);
				}

				newPosition.y = collisionBox.height + staticObject->getCollisionBox().y + 1;
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

void BigEye::updatePosition(){
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
	//this->setAcceleration(FPOINT(0.0f, 0.0f));
}

void BigEye::calculateCollisionBox(){
	if (this->getIsInactive())
		return;
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	FPOINT velocity = this->getVelocity();

	velocity.x += this->getAcceleration().x*deltaTime;
	velocity.y += this->getAcceleration().y*deltaTime;

	// set Collision BOX for kamadoma. 
	BOX collisionBox(this->getPosition().x, this->getPosition().y, BIG_EYE_VIRTUAL_WIDTH,
		BIG_EYE_VIRTUAL_HEIGHT, velocity.x * deltaTime, velocity.y*deltaTime);
	this->setCollisionBox(collisionBox);
}

void BigEye::setState(int state){
	GameObject::setState(state);
	m_animation = AnimationManager::getInstance()->getAnimationSprites(ECharacter::BIG_EYE, state);
	GameObject::setSpriteSpec(m_animation->getSpriteSpecs()[0]);
}

void BigEye::resetToInit(){
	this->setPostion(this->getInitPosition());
	BOX oldCollisionBox = this->getCollisionBox();
	oldCollisionBox.x = this->getPosition().x;
	oldCollisionBox.y = this->getPosition().y;
	oldCollisionBox.width = BIG_EYE_VIRTUAL_WIDTH;
	oldCollisionBox.height = BIG_EYE_VIRTUAL_HEIGHT;
	oldCollisionBox.vx = 0.0f;
	oldCollisionBox.vy = 0.0f;
	this->setCollisionBox(oldCollisionBox);

	this->setState(EState::ACTIVE);
	GameObject::setAcceleration(FPOINT(0, GRAVITATIONAL_ACCELERATION / 2));
	setVelocity(FPOINT(-BIG_EYE_VELOCITY_X, BIG_EYE_VELOCITY_Y));
	this->setAttackDamage(10);
	this->setBlood(20);
}

void BigEye::die(){
	this->setState(EState::DIE);
	this->setIsInactive(true);
	//this->setPostion(this->getInitPosition());
	BOX oldCollisionBox = this->getCollisionBox();
	oldCollisionBox.x = this->getInitPosition().x;
	oldCollisionBox.y = this->getInitPosition().y;
	oldCollisionBox.width = BIG_EYE_VIRTUAL_WIDTH;
	oldCollisionBox.height = BIG_EYE_VIRTUAL_HEIGHT;
	oldCollisionBox.vx = 0.0f;
	oldCollisionBox.vy = 0.0f;
	this->setCollisionBox(oldCollisionBox);
	this->setVelocity(FPOINT(0.0f, 0.0f));
	this->setAcceleration(FPOINT(0.0f, 0.0f));
}
