#include "FlyShell.h"
#include "../../SFramework/Map/ObjectFactory.h"
#include "../../SFramework/Map/ObjectManager.h"

FlyShell::FlyShell()
{
	this->countFrame = 0;
	this->setVelocity(FPOINT(FLY_SHELL_VELOCITY, 0.0f));
	this->isRender = false;
}


FlyShell::~FlyShell()
{
}

void FlyShell::render() {
	this->isRender = true;
	this->countFrame++;
	if (this->getStopUpdateAnimation() == 0){
		SpriteSpec* currentSpriteSpec = m_animation->getCurrentSpriteSpec();
		GameObject::setSpriteSpec(currentSpriteSpec);
	}
	// set position to render
	GameObject::render();
}

void FlyShell::onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector){
	if (collisionTime > 0.0f && collisionTime < 1.0f){
		if (this->getState() == EState::ACTIVE && staticObject->getType() == ECharacter::MEGAMAN_BULLET){
			this->die();
			return;
		}
	}

	if (isRender){
		this->isRender = false;
		if (this->countFrame == 1 * FPS){
			this->setState(EState::ACTIVE);
			// bắn đạn
			createAttack();
		}
		else if (this->countFrame == 1.5f * FPS){
			this->setState(EState::IDLE);
			this->countFrame = 0;
		}
	}
}

void FlyShell::updatePosition(){
	// chỉ update vị trí khi ở trạng thái IDLE
	if (this->getIsInactive() || this->getState() == EState::ACTIVE)
		return;
	FPOINT currentPosition = this->getPosition();
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	FPOINT velocity = this->getVelocity();
	currentPosition.x = currentPosition.x + velocity.x*deltaTime;
	currentPosition.y = currentPosition.y + velocity.y*deltaTime;

	this->setPostion(currentPosition);
}
void FlyShell::calculateCollisionBox(){
	if (this->getIsInactive())
		return;
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	FPOINT velocity = this->getVelocity();

	velocity.x += this->getAcceleration().x*deltaTime;
	velocity.y += this->getAcceleration().y*deltaTime;

	// set Collision BOX for kamadoma. 
	BOX collisionBox(this->getPosition().x, this->getPosition().y, FLY_SHELL_VIRTUAL_WIDTH,
		FLY_SHELL_VIRTUAL_HEIGHT, velocity.x * deltaTime, velocity.y*deltaTime);
	this->setCollisionBox(collisionBox);
}
void FlyShell::setState(int state){
	GameObject::setState(state);
	m_animation = AnimationManager::getInstance()->getAnimationSprites(ECharacter::FLY_SHELL, state);
	GameObject::setSpriteSpec(m_animation->getSpriteSpecs()[0]);
}

void FlyShell::resetToInit(){
	this->setPostion(this->getInitPosition());
	BOX oldCollisionBox = this->getCollisionBox();
	oldCollisionBox.x = this->getPosition().x;
	oldCollisionBox.y = this->getPosition().y;
	oldCollisionBox.width = FLY_SHELL_VIRTUAL_WIDTH;
	oldCollisionBox.height = FLY_SHELL_VIRTUAL_HEIGHT;
	oldCollisionBox.vx = 0.0f;
	oldCollisionBox.vy = 0.0f;
	this->setCollisionBox(oldCollisionBox);
	this->setState(EState::IDLE);
	this->countFrame = 0;
	this->setVelocity(FPOINT(FLY_SHELL_VELOCITY, 0.0f));

}
void FlyShell::die(){
	this->setState(EState::DIE);
	this->setIsInactive(true);
	//this->setPostion(this->getInitPosition());
	BOX oldCollisionBox = this->getCollisionBox();
	oldCollisionBox.x = this->getInitPosition().x;
	oldCollisionBox.y = this->getInitPosition().y;
	oldCollisionBox.width = FLY_SHELL_VIRTUAL_WIDTH;
	oldCollisionBox.height = FLY_SHELL_VIRTUAL_HEIGHT;
	oldCollisionBox.vx = 0.0f;
	oldCollisionBox.vy = 0.0f;
	this->setCollisionBox(oldCollisionBox);
	this->setVelocity(FPOINT(0.0f, 0.0f));
	this->setAcceleration(FPOINT(0.0f, 0.0f));
}

void FlyShell::createBullet(float vx, float vy){
	GameObject* blasterBullet = ObjectFactory::createObject(ECharacter::SCREW_BULLET);
	blasterBullet->setObjectID(ObjectManager::notInMapObjectId++);
	blasterBullet->setVelocity(FPOINT(vx, vy));
	blasterBullet->setPostion(FPOINT(this->getPosition().x + FLY_SHELL_VIRTUAL_WIDTH / 2, this->getPosition().y - FLY_SHELL_VIRTUAL_HEIGHT / 2));
	blasterBullet->calculateCollisionBox();

	ObjectManager::getInstance()->addObjectToActiveObject(blasterBullet);
}

void FlyShell::createAttack(){
	createBullet(-FLY_SHELL_BULLET_VELOCITY, 0.0f);
	createBullet(-FLY_SHELL_BULLET_VELOCITY, FLY_SHELL_BULLET_VELOCITY);
	createBullet(0.0f, FLY_SHELL_BULLET_VELOCITY);
	createBullet(FLY_SHELL_BULLET_VELOCITY, FLY_SHELL_BULLET_VELOCITY);
	createBullet(FLY_SHELL_BULLET_VELOCITY, 0.0f);
	createBullet(FLY_SHELL_BULLET_VELOCITY, -FLY_SHELL_BULLET_VELOCITY);
	createBullet(0.0f, -FLY_SHELL_BULLET_VELOCITY);
	createBullet(-FLY_SHELL_BULLET_VELOCITY, -FLY_SHELL_BULLET_VELOCITY);
}