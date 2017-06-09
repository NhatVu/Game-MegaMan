#include "Blader.h"
#include "../../SFramework/SFramework.h"
#include <cmath>
Blader::Blader()
{
	attackCountFrame = 0;
	this->setVelocity(FPOINT(BLADER_VELOCITY_X, 0.0f));
	this->isAttacked = false;
	this->attackPos = FPOINT(0.0f, 0.0f);
	this->setAttackDamage(3);
	this->setBlood(1);
}


Blader::~Blader()
{
}

void Blader::render() {
	if (this->isAttacked)
		this->attackCountFrame++;
	SpriteSpec* currentSpriteSpec = m_animation.getCurrentSpriteSpec();
	GameObject::setSpriteSpec(currentSpriteSpec);
	// set position to render
	GameObject::render();
}
void Blader::onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector){
#pragma region Collision With Megaman
	if (staticObject->getType() == ECharacter::MEGAMAN){
		FPOINT megaManPos = staticObject->getPosition();
		FPOINT bladerPos = this->getPosition();
		FPOINT velocity = this->getVelocity();
		DWORD deltaTime = GameTime::getInstance()->getDeltaTime();

		if (this->attackCountFrame == 0 && bladerPos.x - megaManPos.x > BLADER_FORCE_ATTACK_DISTANCE){
			velocity.x = -BLADER_VELOCITY_X;
			velocity.y = 0.0f;

		}
		else if (this->attackCountFrame == 0 && megaManPos.x - bladerPos.x > BLADER_FORCE_ATTACK_DISTANCE){
			velocity.x = BLADER_VELOCITY_X;
			velocity.y = 0.0f;

			//	this->isAttacked = true;
		}
		else{
			if (abs(megaManPos.x - bladerPos.x) > 20.0f){

				this->isAttacked = true;
				if (attackCountFrame == 0){
					this->attackPos = megaManPos;
					this->attackPos.y -= staticObject->getSpriteSpec()->getHeight() / 2;
					// tính vận tốc vx, vy để đụng vị trí của megaman
					velocity.x = (attackPos.x - bladerPos.x) / (deltaTime * FRAME_ATTACK);
					//velocity.x = BLADER_FORCE_ATTACK_DISTANCE / (deltaTime * 6);
					velocity.y = (attackPos.y - bladerPos.y) / (deltaTime * FRAME_ATTACK);
				}
			}
		}

		if (this->attackCountFrame == FRAME_ATTACK){
			// đụng vị trí attackPos => đảo chiều vy
			velocity.y *= -1;
			this->attackCountFrame++; // trick, vì vòng lặp for kiểm tra va chạm
		}
		else if (this->attackCountFrame >= 1.5*FRAME_ATTACK && (abs(attackPos.x - bladerPos.x) >= BLADER_FORCE_ATTACK_DISTANCE ||
			abs(bladerPos.y > this->getInitPosition().y))){
			//	if (bladerPos.y < this->getInitPosition().y)
			this->setPostion(FPOINT(this->getPosition().x, this->getInitPosition().y));
			velocity.y = 0.0f;
			this->attackCountFrame = 0;
			this->isAttacked = false;
		}

		this->setVelocity(velocity);

	}
#pragma endregion

	if (collisionTime > 0.0f && collisionTime <= 1.0f){
		if (staticObject->getType() == ECharacter::MEGAMAN_BULLET && staticObject->getType() != EState::DIE){
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

}
void Blader::updatePosition(){
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
void Blader::calculateCollisionBox(){
	if (this->getIsInactive())
		return;
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	FPOINT velocity = this->getVelocity();

	velocity.x += this->getAcceleration().x*deltaTime;
	velocity.y += this->getAcceleration().y*deltaTime;

	// set Collision BOX for kamadoma. 
	BOX collisionBox(this->getPosition().x, this->getPosition().y, BLADER_VIRTUAL_WIDTH,
		BLADER_VIRTUAL_HEIGHT, velocity.x * deltaTime, velocity.y*deltaTime);
	this->setCollisionBox(collisionBox);
}
void Blader::setState(int state){
	GameObject::setState(state);
	m_animation = *AnimationManager::getInstance()->getAnimationSprites(ECharacter::BLADER, state);
	GameObject::setSpriteSpec(m_animation.getSpriteSpecs()[0]);
}

void Blader::resetToInit(){
	this->setPostion(this->getInitPosition());
	BOX oldCollisionBox = this->getCollisionBox();
	oldCollisionBox.x = this->getPosition().x;
	oldCollisionBox.y = this->getPosition().y;
	oldCollisionBox.width = BLADER_VIRTUAL_WIDTH;
	oldCollisionBox.height = BLADER_VIRTUAL_HEIGHT;
	oldCollisionBox.vx = 0.0f;
	oldCollisionBox.vy = 0.0f;
	this->setCollisionBox(oldCollisionBox);

	this->setState(EState::ACTIVE);
	this->attackCountFrame = 0;
	this->isAttacked = false;
	this->attackPos = FPOINT(0.0f, 0.0f);
	this->setAttackDamage(3);
	this->setBlood(1);
}
void Blader::die(){
	this->setState(EState::DIE);
	this->setIsInactive(true);
	//this->setPostion(this->getInitPosition());
	BOX oldCollisionBox = this->getCollisionBox();
	oldCollisionBox.x = this->getInitPosition().x;
	oldCollisionBox.y = this->getInitPosition().y;
	oldCollisionBox.width = BLADER_VIRTUAL_WIDTH;
	oldCollisionBox.height = BLADER_VIRTUAL_HEIGHT;
	oldCollisionBox.vx = 0.0f;
	oldCollisionBox.vy = 0.0f;
	this->setCollisionBox(oldCollisionBox);
	this->setVelocity(FPOINT(0.0f, 0.0f));
	this->setAcceleration(FPOINT(0.0f, 0.0f));
}
