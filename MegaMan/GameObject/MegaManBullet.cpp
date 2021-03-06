#include "MegaManBullet.h"
#include "MegaMan.h"

MegaManBullet::MegaManBullet()
{
	setAcceleration(FPOINT(0.0f, 0.0f));
	this->setAttackDamage(1);
}


MegaManBullet::~MegaManBullet()
{
}

void MegaManBullet::setState(int state){
//	this->state = state;
	GameObject::setState(state);
	m_animation = AnimationManager::getInstance()->getAnimationSprites(ECharacter::MEGAMAN_BULLET, state);
	GameObject::setSpriteSpec(m_animation->getSpriteSpecs()[0]);
}
void MegaManBullet::render() {
	SpriteSpec* currentSpriteSpec = m_animation->getCurrentSpriteSpec();
	GameObject::setSpriteSpec(currentSpriteSpec);
	// set position to render
	GameObject::render();
}

void MegaManBullet::initFire(){
	GameObject* megaMan = ObjectManager::getInstance()->getMegaMan();
	FPOINT initPos = megaMan->getPosition();
	//megaManPos.y = 2.0f / 3 * megaManPos.y;
	int flipVertical = megaMan->getFlipVertical(); // = 1, quay sang phai
	if (flipVertical == 1)
		initPos.x += flipVertical * MEGA_MAN_VIRTUAL_WIDTH + flipVertical;
	else initPos.x = initPos.x - MEGAMAN_BULLET_VIRTUAL_WIDTH - 1;
	initPos.y -= MEGAMAN_BULLET_VIRTUAL_HEIGHT / 2;

	this->setPostion(initPos);

	setVelocity(FPOINT(MEGAMAN_BULLET_VELOCITY_X*flipVertical, 0.0f));

	BOX collisionBox(this->getPosition().x, this->getPosition().y, MEGAMAN_BULLET_VIRTUAL_WIDTH,
		MEGAMAN_BULLET_VIRTUAL_HEIGHT, 0.0f, 0.0f);
	this->setCollisionBox(collisionBox);

}

void MegaManBullet::calculateCollisionBox(){
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	FPOINT velocity = this->getVelocity();


	velocity.x += this->getAcceleration().x*deltaTime;
	velocity.y += this->getAcceleration().y*deltaTime;
	

	// set Collision BOX for kamadoma. 
	BOX collisionBox(this->getPosition().x, this->getPosition().y, MEGAMAN_BULLET_VIRTUAL_WIDTH,
		MEGAMAN_BULLET_VIRTUAL_HEIGHT, velocity.x * deltaTime, velocity.y*deltaTime);
	this->setCollisionBox(collisionBox);
}
void MegaManBullet::onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector){
	SpriteSpec* currentSpriteSpec = this->getSpriteSpec();

	int staticObjectType = staticObject->getType();
	D3DXVECTOR2 normal = collisionVector;
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	FPOINT velocity = this->getVelocity();
	if (collisionTime > 0.0f && collisionTime <= 1.0f){
	
		switch (staticObjectType)
		{
		case ECharacter::KAMADOMA:
		case ECharacter::BLADER:
		case ECharacter::BIG_EYE:
		case ECharacter::FLY_SHELL:
		case ECharacter::SUZY:
		case ECharacter::SCREW:
		case ECharacter::BLASTER:
			this->setState(EState::DIE);
			this->setIsInactive(true);
			break;
		default:
			break;
		}
	}
}
void MegaManBullet::updatePosition(){
	FPOINT currentPosition = this->getPosition();
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	FPOINT velocity = this->getVelocity();
	currentPosition.x = currentPosition.x + velocity.x*deltaTime;
	currentPosition.y = currentPosition.y + velocity.y*deltaTime;

	//velocity.x = KAMADOMA_VELOCITY_X;
	this->setPostion(currentPosition);

}
