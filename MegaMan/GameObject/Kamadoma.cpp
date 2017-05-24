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


void Kamadoma::render() {
	SpriteSpec* currentSpriteSpec = m_animation->getCurrentSpriteSpec();
	GameObject::setSpriteSpec(currentSpriteSpec);
	// set position to render
	GameObject::render();
}
void Kamadoma::onKeyDown(int keyCode) {}
void Kamadoma::onKeyUp(int keyCode) {}

void Kamadoma::processKeyState(BYTE *keyState){}
void Kamadoma::onCollision(GameObject* staticObject){
	SpriteSpec* currentSpriteSpec = this->getSpriteSpec();

	int staticObjectType = staticObject->getType();
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	FPOINT velocity = this->getVelocity();


	velocity.x += this->getAcceleration().x*deltaTime;
	velocity.y += this->getAcceleration().y*deltaTime;
	D3DXVECTOR2 normal;

	// set Collision BOX for kamadoma. 
	BOX collisionBox(this->getPosition().x, this->getPosition().y, KAMADOMA_VIRTUAL_WIDTH,
		KAMADOMA_VIRTUAL_HEIGHT, velocity.x * deltaTime, velocity.y*deltaTime);
	this->setCollisionBox(collisionBox);

	// collision
	
	float collisionTime = Collision::CheckCollision(this, staticObject, normal);
	if (collisionTime > 0.0f && collisionTime < 1.0f){
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

				if (megaManPos.x - newPosition.x > KAMADOMA_FORCE_ATTACK_DISTANCE){
					velocity.x = KAMADOMA_VELOCITY_X;
					canAttack = true;
				}
				else if (newPosition.x - megaManPos.x > KAMADOMA_FORCE_ATTACK_DISTANCE){
					velocity.x = -KAMADOMA_VELOCITY_X;
					canAttack = true;
				}
				else if (canAttack){
					int numberFrame = (KAMADOMA_VELOCITY_Y / (-GRAVITATIONAL_ACCELERATION/2 * deltaTime)) * 2 ;
					velocity.x = (megaManPos.x - newPosition.x) / (deltaTime * numberFrame);
					canAttack = false;
				}

				if (isRightCollision){
					velocity.x = -1.5f*KAMADOMA_VELOCITY_X;
				}
				else if(isLeftCollision) velocity.x = 1.5f*KAMADOMA_VELOCITY_X;

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
				isRightCollision = true;
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
	oldCollisionBox.vx = 0.0f;
	oldCollisionBox.vy = 0.0f;
	this->setCollisionBox(oldCollisionBox);

	this->setState(EState::ACTIVE);

}