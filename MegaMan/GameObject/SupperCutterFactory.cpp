#include "SupperCutterFactory.h"
#include "SuperCutter.h"
#include <cmath>
#include "../../SFramework/Map/ObjectFactory.h"
#include "../../SFramework/Map/ObjectManager.h"
#include "MegaMan.h"

SupperCutterFactory::SupperCutterFactory()
{
	this->countFrame = 0;
	this->isRender = false;
	this->canAttack = false;
}


SupperCutterFactory::~SupperCutterFactory()
{
}
void SupperCutterFactory::render() {
	this->isRender = true;
	if (this->canAttack)
		this->countFrame++;
	//GameObject::render();
}

void SupperCutterFactory::onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector){
	if (this->isRender){
		this->isRender = false;
		FPOINT megaManPos = staticObject->getPosition();
		DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
		FPOINT superCutterFactoryPos = this->getPosition();
		if (std::abs(megaManPos.x - this->getPosition().x) < SUPPER_CUTTER_FACTORY_ATTACK_DISTANCE){
			this->canAttack = true;


			if (this->countFrame == 0.5 * FPS){
				// bắn loạt đạn thứ nhất
				FPOINT superCutterVelocity;
				int numberFrame = (SUPER_CUTTER_VELOCITY_Y / (-GRAVITATIONAL_ACCELERATION/2 * deltaTime)) * 2;
				int flipVertical;
				if (megaManPos.x < superCutterFactoryPos.x)
					flipVertical = 1;
				else flipVertical = -1;
				superCutterVelocity.x = (megaManPos.x + MEGA_MAN_VIRTUAL_WIDTH/2*flipVertical - superCutterFactoryPos.x) / (deltaTime * numberFrame);
				superCutterVelocity.y = SUPER_CUTTER_VELOCITY_Y;
				createSuperCutter(superCutterVelocity.x, superCutterVelocity.y);
				this->countFrame = 0;
			}

		}
		else {
			this->canAttack = false;
			this->countFrame = 0;
		}
	}
}
void SupperCutterFactory::updatePosition(){}
void SupperCutterFactory::calculateCollisionBox(){}
void SupperCutterFactory::setState(int state){}

void SupperCutterFactory::resetToInit(){}

void SupperCutterFactory::createSuperCutter(float vx, float vy){
	GameObject* superCutter = ObjectFactory::createObject(ECharacter::SUPER_CUTTER);
	superCutter->setObjectID(ObjectManager::notInMapObjectId++);
	superCutter->setVelocity(FPOINT(vx, vy));
	superCutter->setPostion(this->getPosition());
	superCutter->calculateCollisionBox();
	if (vx > 0)
		superCutter->setFlipVertical(-1);
	ObjectManager::getInstance()->addObjectToActiveObject(superCutter);
}

