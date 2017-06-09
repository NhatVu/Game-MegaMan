#include "MegaManBeAttackedState.h"


MegaManBeAttackedState::MegaManBeAttackedState()
{
	this->changeToAttackedFinish = false;
	this->ChangeToIdleState = false;
	this->countFrame = 0;
	this->name = "BeAttacked";
}


MegaManBeAttackedState::~MegaManBeAttackedState()
{
}

void MegaManBeAttackedState::update(GameObject* gameObject) {}
void MegaManBeAttackedState::enter(GameObject* gameObject){
	((MegaMan*)gameObject)->changeAnimation(ECharacter::MEGAMAN, EState::ATTACKED_BEGIN);
	gameObject->setState(EState::ATTACKED_BEGIN);
	if (this->changeToAttackedFinish){
		((MegaMan*)gameObject)->changeAnimation(ECharacter::MEGAMAN, EState::ATTACKED_FINISH);
		gameObject->setState(EState::ATTACKED_FINISH);
		this->changeToAttackedFinish = false;
	}

}
GameState* MegaManBeAttackedState::onCollision(GameObject* gameObject, GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector) {
	
	if (this->ChangeToIdleState){
		this->ChangeToIdleState = false;
		this->countFrame = 0;
		gameObject->setAcceleration(FPOINT(MEGA_MAN_ACCELERATION_X, 0.0f));
		gameObject->setVelocity(FPOINT(gameObject->getVelocity().x, 0.0f));
		return new MegaManIdleState();
	}
	
	D3DXVECTOR2 normal = collisionVector;
	// xet va cham voi static
	FPOINT newPosition = gameObject->getPosition();
	if (collisionTime > 0.0f && collisionTime < 1.0f){
		gameObject->setNoCollisionWithAll(false);

		// tu tren xuong
		if (normal.x == 0.0f && normal.y == 1.0f){
			if (staticObject->getType() == ECharacter::STATIC || staticObject->getType() == ECharacter::LADDER){
				newPosition.y = MEGA_MAN_VIRTUAL_HEIGHT + staticObject->getCollisionBox().y + 1;
				gameObject->setPostion(newPosition);
				/*
				Khi mega man đứng trên mặt đất, có phản lực N triệt tiêu lực hấp dẫn. Do đó có thể coi
				gia tốc trọng từng = 0 và v.y = 0;
				*/
				gameObject->setAcceleration(FPOINT(MEGA_MAN_ACCELERATION_X, 0.0f));
				gameObject->setVelocity(FPOINT(gameObject->getVelocity().x, 0.0f));
				return NULL;
			}
		}// vật đi chuyển từ dưới lên
		else if (normal.x == 0.0f && normal.y == -1.0f)
		{
			if (staticObject->getType() == ECharacter::STATIC)
			{
				newPosition.y = staticObject->getCollisionBox().y - staticObject->getCollisionBox().height - 1;
				gameObject->setPostion(newPosition);
				/*
				Khi mega man đứng trên mặt đất, có phản lực N triệt tiêu lực hấp dẫn. Do đó có thể coi
				gia tốc trọng từng = 0 và v.y = 0;
				*/
				gameObject->setAcceleration(FPOINT(MEGA_MAN_ACCELERATION_X, 0.0f));
				//gameObject->setVelocity(FPOINT(gameObject->getVelocity().x, 0.0f));
				return NULL;
			}
		}
	}
	if (collisionTime == 1.0f){
		if (staticObject->getType() == ECharacter::STATIC){
			if (newPosition.x + MEGA_MAN_VIRTUAL_WIDTH < staticObject->getCollisionBox().x)
				newPosition.x = staticObject->getCollisionBox().x - MEGA_MAN_VIRTUAL_WIDTH - 5;
			else if (staticObject->getCollisionBox().x + staticObject->getCollisionBox().width < newPosition.x)
				newPosition.x = staticObject->getCollisionBox().x + staticObject->getCollisionBox().width + 1;


			gameObject->setPostion(newPosition);
		}
	}
	return NULL;
}