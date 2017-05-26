#include "BombombombParent.h"
#include "BombombombChildren.h"

BombombombParent::BombombombParent()
{
	this->countFrame = 0;
	this->deactiveInterval = false;
	setVelocity(FPOINT(0.0f, BOMBOMBOMB_PARENT_VELOCITY_Y));
}



BombombombParent::~BombombombParent()
{
}

GameObject* BombombombParent::createBombombombChldren(float velocity_x){
	GameObject* bombombombChildren = ObjectFactory::createObject(ECharacter::BOMBOMBOM_CHILDREN);
	bombombombChildren->setObjectID(ObjectManager::notInMapObjectId++);
	bombombombChildren->setVelocity(FPOINT(velocity_x, BOMBOMBOMB_CHILDREN_VELOCITY_Y));
	bombombombChildren->setAcceleration(FPOINT(0.0f, GRAVITATIONAL_ACCELERATION / 5));
	bombombombChildren->setInitPosition(FPOINT(this->getPosition().x, BOMBOMBOMB_PARENT_EXPLOSIVE_HEIGHT));
	bombombombChildren->resetToInit();
	bombombombChildren->setIsInactive(true);

	return bombombombChildren;
}

void BombombombParent::setState(int state){
	GameObject::setState(state);
	m_animation = AnimationManager::getInstance()->getAnimationSprites(ECharacter::BOMBOMBOMB_PARENT, state);
	GameObject::setSpriteSpec(m_animation->getSpriteSpecs()[0]);
}
void BombombombParent::render() {
	//if (this->getIsInactive())
	//
	if (this->deactiveInterval){
		if (countFrame == 0){
			SpriteSpec* currentSpriteSpec = m_animation->getCurrentSpriteSpec();
			GameObject::setSpriteSpec(currentSpriteSpec);
			// set position to render
			GameObject::render();
		}
		this->countFrame++;
		if (this->countFrame > 3 * FPS){
			this->countFrame = 0;
			this->deactiveInterval = false;
			this->resetToInit();
		}
		return;
	}
	SpriteSpec* currentSpriteSpec = m_animation->getCurrentSpriteSpec();
	GameObject::setSpriteSpec(currentSpriteSpec);
	// set position to render
	GameObject::render();
}

void BombombombParent::onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector){
	// nếu megaman va chạm với bombombomb_parent => mega man bị mất máu.
	// không xét va chạm với ai cả. chỉ xét trường hợp nếu > vị trí nổ => die (đồng nghĩa với việc nổ)
	FPOINT position = this->getPosition();
	if (this->getState() == EState::DIE)
		return;
	if (position.y > BOMBOMBOMB_PARENT_EXPLOSIVE_HEIGHT){
		this->die();
		if (listBombombombChildren.size() == 0){
			//init bombombomb children

			listBombombombChildren.push_back(createBombombombChldren(BOMBOMBOMB_CHILDREN_VELOCITY_X_STANDARD));
			listBombombombChildren.push_back(createBombombombChldren(-BOMBOMBOMB_CHILDREN_VELOCITY_X_STANDARD));
			listBombombombChildren.push_back(createBombombombChldren(1.4 * BOMBOMBOMB_CHILDREN_VELOCITY_X_STANDARD));
			listBombombombChildren.push_back(createBombombombChldren(-1.4 * BOMBOMBOMB_CHILDREN_VELOCITY_X_STANDARD));
		}
		// active bombombomb chldren
		map<int, GameObject*> active = ObjectManager::getInstance()->getActiveObject();
		for (int i = 0; i < listBombombombChildren.size(); i++){
			listBombombombChildren[i]->setIsInactive(false);
			listBombombombChildren[i]->resetToInit(); // do chưa ra khỏi viewport nên không gọi được trong hàm processQuadTreeAndViewport
			ObjectManager::getInstance()->addObjectToActiveObject(listBombombombChildren[i]);
		}
	}
}
void BombombombParent::updatePosition(){
	if (this->getIsInactive() || this->deactiveInterval)
		return;
	FPOINT currentPosition = this->getPosition();
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	FPOINT velocity = this->getVelocity();
	currentPosition.x = currentPosition.x + velocity.x*deltaTime;
	currentPosition.y = currentPosition.y + velocity.y*deltaTime;

	this->setPostion(currentPosition);
	this->setVelocity(velocity);
}
void BombombombParent::calculateCollisionBox(){
	if (this->getIsInactive() || this->deactiveInterval)
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

void BombombombParent::resetToInit(){

	this->setPostion(this->getInitPosition());
	BOX oldCollisionBox = this->getCollisionBox();
	oldCollisionBox.x = this->getPosition().x;
	oldCollisionBox.y = this->getPosition().y;
	oldCollisionBox.vx = 0.0f;
	oldCollisionBox.vy = 0.0f;
	this->setCollisionBox(oldCollisionBox);
	this->setState(EState::ACTIVE);
}
void BombombombParent::die(){
	this->setState(EState::DIE);
	this->deactiveInterval = true;
	BOX oldCollisionBox = this->getCollisionBox();
	oldCollisionBox.x = this->getInitPosition().x;
	oldCollisionBox.y = this->getInitPosition().y;
	oldCollisionBox.vx = 0.0f;
	oldCollisionBox.vy = 0.0f;
	this->setCollisionBox(oldCollisionBox);

}