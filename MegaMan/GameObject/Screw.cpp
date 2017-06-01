#include "Screw.h"
#include <cmath>
#include "../../SFramework/Map/ObjectFactory.h"
#include "../../SFramework/Map/ObjectManager.h"
Screw::Screw()
{
	this->canAttack = false;
	this->countFrame = 0;
}


Screw::~Screw()
{
}

void Screw::render() {
	if (this->canAttack)
		this->countFrame++;
	if (this->getStopUpdateAnimation() == 0){
		SpriteSpec* currentSpriteSpec = m_animation->getCurrentSpriteSpec();
		GameObject::setSpriteSpec(currentSpriteSpec);
	}
	// set position to render
	GameObject::render();
}

void Screw::onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector){
	if (collisionTime > 0.0f && collisionTime < 1.0f){
		if (this->getState() == EState::ACTIVE && staticObject->getType() == ECharacter::MEGAMAN_BULLET){
			this->die();
			return;
		}
	}

	if (staticObject->getType() == ECharacter::MEGAMAN){
		FPOINT megaManPos = staticObject->getPosition();
		if (std::abs(megaManPos.x - this->getPosition().x) < SCREW_FORCE_ATTACK_DISTANCE){
			this->canAttack = true;
			if (this->getState() == EState::IDLE && this->countFrame == 0){
				this->setState(EState::ACTIVE);
				this->countFrame = 0;
			}

			if (this->countFrame == 0.5 * FPS){
				// bắn loạt đạn thứ nhất
				createAttack();
			}
			else if (this->countFrame == 1.5f*FPS){
				// bắn loạt đạn thứ hai
				createAttack();
			}
			else if (this->countFrame == 2 * FPS){
				// idle trong 1s
				this->setState(EState::IDLE);
			}
			else if (this->countFrame == 3 * FPS){
				this->setState(EState::ACTIVE);
				this->countFrame = 0;
			}
		}
		else {
			this->canAttack = false;
			this->setState(EState::IDLE);
			this->countFrame = 0;
		}
	}
}
void Screw::updatePosition(){}
void Screw::calculateCollisionBox(){}
void Screw::setState(int state){
	GameObject::setState(state);
	m_animation = AnimationManager::getInstance()->getAnimationSprites(ECharacter::SCREW, state);
	GameObject::setSpriteSpec(m_animation->getSpriteSpecs()[0]);
}

void Screw::resetToInit(){
	this->setPostion(this->getInitPosition());
	BOX oldCollisionBox = this->getCollisionBox();
	oldCollisionBox.x = this->getPosition().x;
	oldCollisionBox.y = this->getPosition().y;
	oldCollisionBox.width = SCREW_VIRTUAL_WIDTH;
	oldCollisionBox.height = SCREW_VIRTUAL_HEIGHT;
	oldCollisionBox.vx = 0.0f;
	oldCollisionBox.vy = 0.0f;
	this->setCollisionBox(oldCollisionBox);
	this->setState(EState::ACTIVE);
}
void Screw::die(){
	this->setState(EState::DIE);
	this->setIsInactive(true);
	//this->setPostion(this->getInitPosition());
	BOX oldCollisionBox = this->getCollisionBox();
	oldCollisionBox.x = this->getInitPosition().x;
	oldCollisionBox.y = this->getInitPosition().y;
	oldCollisionBox.width = SCREW_VIRTUAL_WIDTH;
	oldCollisionBox.height = SCREW_VIRTUAL_HEIGHT;
	oldCollisionBox.vx = 0.0f;
	oldCollisionBox.vy = 0.0f;
	this->setCollisionBox(oldCollisionBox);
	this->setVelocity(FPOINT(0.0f, 0.0f));
	this->setAcceleration(FPOINT(0.0f, 0.0f));
}

void Screw::createScrewBullet(float vx, float vy){
	vx *= this->getFlipVertical();
	GameObject* blasterBullet = ObjectFactory::createObject(ECharacter::SCREW_BULLET);
	blasterBullet->setObjectID(ObjectManager::notInMapObjectId++);
	blasterBullet->setVelocity(FPOINT(vx, vy));
	blasterBullet->setPostion(this->getPosition());
	blasterBullet->calculateCollisionBox();

	ObjectManager::getInstance()->addObjectToActiveObject(blasterBullet);
}

void Screw::createAttack(){
	createScrewBullet(-SCREW_BULLET_VELOCITY_X, 0.0f);
	createScrewBullet(-SCREW_BULLET_VELOCITY_X, SCREW_BULLET_VELOCITY_X);
	createScrewBullet(0.0f, SCREW_BULLET_VELOCITY_X);
	createScrewBullet(SCREW_BULLET_VELOCITY_X, SCREW_BULLET_VELOCITY_X);
	createScrewBullet(SCREW_BULLET_VELOCITY_X, 0.0f);
}
