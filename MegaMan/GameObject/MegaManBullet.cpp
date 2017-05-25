#include "MegaManBullet.h"
#include "MegaMan.h"

MegaManBullet::MegaManBullet()
{
	setAcceleration(FPOINT(0.0f, 0.0f));
}


MegaManBullet::~MegaManBullet()
{
}

void MegaManBullet::render() {
	SpriteSpec* currentSpriteSpec = m_animation->getCurrentSpriteSpec();
	GameObject::setSpriteSpec(currentSpriteSpec);
	// set position to render
	GameObject::render();
}
void MegaManBullet::onKeyDown(int keyCode) {}
void MegaManBullet::onKeyUp(int keyCode) {}
void MegaManBullet::initFire(){
	GameObject* megaMan = ObjectManager::getInstance()->getMegaMan();
	FPOINT initPos = megaMan->getPosition();
	//megaManPos.y = 2.0f / 3 * megaManPos.y;
	int flipVertical = megaMan->getFlipVertical(); // = 1, quay sang phai
	initPos.x += flipVertical * MEGA_MAN_VIRTUAL_WIDTH;
	initPos.y -= MEGAMAN_BULLET_VIRTUAL_HEIGHT / 2;

	this->setPostion(initPos);

	setVelocity(FPOINT(MEGAMAN_BULLET_VELOCITY_X*flipVertical, 0.0f));

	BOX collisionBox(this->getPosition().x, this->getPosition().y, MEGAMAN_BULLET_VIRTUAL_WIDTH,
		MEGAMAN_BULLET_VIRTUAL_HEIGHT, 0.0f, 0.0f);
	this->setCollisionBox(collisionBox);

}
void MegaManBullet::processKeyState(BYTE *keyState){}
void MegaManBullet::onCollision(GameObject* staticObject){
	SpriteSpec* currentSpriteSpec = this->getSpriteSpec();

	int staticObjectType = staticObject->getType();
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	FPOINT velocity = this->getVelocity();


	velocity.x += this->getAcceleration().x*deltaTime;
	velocity.y += this->getAcceleration().y*deltaTime;
	D3DXVECTOR2 normal;

	// set Collision BOX for kamadoma. 
	BOX collisionBox(this->getPosition().x, this->getPosition().y, MEGAMAN_BULLET_VIRTUAL_WIDTH,
		MEGAMAN_BULLET_VIRTUAL_HEIGHT, velocity.x * deltaTime, velocity.y*deltaTime);
	this->setCollisionBox(collisionBox);
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
