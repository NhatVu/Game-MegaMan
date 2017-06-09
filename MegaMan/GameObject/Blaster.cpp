#include "Blaster.h"
#include "../../SFramework/SFramework.h"
#include "BlasterBullet.h"

bool Blaster::reversedFirtTime = false;
Blaster::Blaster()
{
	this->isRender = false;
	this->setAttackDamage(1);
	this->setBlood(1);
}


Blaster::~Blaster()
{
}

void Blaster::render() {
	this->countFrame++;
	this->isRender = true;
	if (this->getStopUpdateAnimation() == 0){

		SpriteSpec* currentSpriteSpec = m_animation.getCurrentSpriteSpec();
		GameObject::setSpriteSpec(currentSpriteSpec);
	}
	// set position to render
	GameObject::render();
}

void Blaster::onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector){
	// blaster chết khi nó đang open (active)
	if (collisionTime > 0.0f && collisionTime <= 1.0f){
		if (this->getState() == EState::ACTIVE && staticObject->getType() == ECharacter::MEGAMAN_BULLET && staticObject->getType() != EState::DIE){
			int blood = this->getBlood();
			int staticAttackDamage = staticObject->getAttackDamage();
			blood -= staticAttackDamage;
			if (blood <= 0){
				this->die();
				return;
			}
			else this->setBlood(blood);
		}
	}

#pragma region dicide when to fire bullet

	if (this->isRender){
		this->isRender = false;

		// nếu đã idle trong 2s => chuyển sang active
		if (this->countFrame == 2 * FPS){
			this->setState(EState::ACTIVE);
			// bắn viên đạn thứ nhất
			creaetBlasterBullet(-BLASTER_BULLET_VELOCITY_X, 0.707f*BLASTER_BULLET_VELOCITY_X);
			//this->countFrame++;
		}
		else if (this->countFrame == 2 * FPS + m_animation.getSpriteSpecs().size()){
			this->setStopUpdateAnimation(true);
		}
		else if (this->countFrame == 2.5f * FPS){
			// bắn viên đạn thứ 2
			creaetBlasterBullet(-BLASTER_BULLET_VELOCITY_X, 0.0f);
			//this->countFrame++;
		}

		else if (this->countFrame == 3 * FPS){
			// bắn viên thứ 3
			creaetBlasterBullet(-BLASTER_BULLET_VELOCITY_X, -0.707*BLASTER_BULLET_VELOCITY_X);
			//this->countFrame++;
		}
		else if (this->countFrame == 3.5f * FPS){
			// bắn viên thứ 4
			creaetBlasterBullet(-BLASTER_BULLET_VELOCITY_X, -0.09f);
			// đóng blaster => reverse animation order
			//if (Blaster::reversedFirtTime == false){
				Blaster::reversedFirtTime = true;
				m_animation.reverseAnimation();
			//}
			GameObject::setSpriteSpec(m_animation.getSpriteSpecs()[0]);
			this->setStopUpdateAnimation(false);
			//this->countFrame++;
		}
		else if (this->countFrame == 3.5f * FPS + m_animation.getSpriteSpecs().size()){
			// sau khi đã đóng xong => chuyển vể idle
			//if (Blaster::reversedFirtTime){
				Blaster::reversedFirtTime = false;
				m_animation.reverseAnimation();
			//}
			this->setState(EState::IDLE);
			this->countFrame = 0;
		}
	}
#pragma endregion


}

// vật tĩnh, không di chuyển => ko update pos
void Blaster::updatePosition(){}


void Blaster::calculateCollisionBox(){
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
void Blaster::setState(int state){
	GameObject::setState(state);
	m_animation = *(AnimationManager::getInstance()->getAnimationSprites(ECharacter::BLASTER, state));
	GameObject::setSpriteSpec(m_animation.getSpriteSpecs()[0]);
}

void Blaster::resetToInit(){
	this->setPostion(this->getInitPosition());
	BOX oldCollisionBox = this->getCollisionBox();
	oldCollisionBox.x = this->getPosition().x;
	oldCollisionBox.y = this->getPosition().y;
	oldCollisionBox.width = this->getSpriteSpec()->getWidth();
	oldCollisionBox.height = this->getSpriteSpec()->getHeight();
	oldCollisionBox.vx = 0.0f;
	oldCollisionBox.vy = 0.0f;
	this->setCollisionBox(oldCollisionBox);

	this->setState(EState::IDLE);
	this->countFrame = 0;
	this->setAttackDamage(3);
	this->setBlood(1);
}

void Blaster::die(){
	this->setState(EState::DIE);
	this->setIsInactive(true);
	//this->setPostion(this->getInitPosition());
	BOX oldCollisionBox = this->getCollisionBox();
	oldCollisionBox.x = this->getInitPosition().x;
	oldCollisionBox.y = this->getInitPosition().y;
	oldCollisionBox.width = this->getSpriteSpec()->getWidth();
	oldCollisionBox.height = this->getSpriteSpec()->getHeight();
	oldCollisionBox.vx = 0.0f;
	oldCollisionBox.vy = 0.0f;
	this->setCollisionBox(oldCollisionBox);
	this->setVelocity(FPOINT(0.0f, 0.0f));
	this->setAcceleration(FPOINT(0.0f, 0.0f));
}

void Blaster::creaetBlasterBullet(float vx, float vy){
	vx *= this->getFlipVertical();
	GameObject* blasterBullet = ObjectFactory::createObject(ECharacter::BLASTER_BULLET);
	blasterBullet->setObjectID(ObjectManager::notInMapObjectId++);
	blasterBullet->setVelocity(FPOINT(vx, vy));
	blasterBullet->setPostion(FPOINT(this->getPosition().x - this->getFlipVertical()*(this->getSpriteSpec()->getWidth() - 5), this->getPosition().y - this->getSpriteSpec()->getHeight() / 2));
	blasterBullet->calculateCollisionBox();
	//blasterBullet->setAcceleration(FPOINT(0.0f, GRAVITATIONAL_ACCELERATION / 5));
	//blasterBullet->resetToInit();
	//blasterBullet->setIsInactive(true);

	ObjectManager::getInstance()->addObjectToActiveObject(blasterBullet);
}