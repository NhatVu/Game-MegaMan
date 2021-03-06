﻿#include "MegaManAttackState.h"
#include "../../../SFramework/Map/ObjectFactory.h"
#include "../../../SFramework/SpriteAndAnimation/TextureManager.h"

MegaManAttackState::MegaManAttackState()
{
	this->name = "Attack";
	this->isFinishAttack = true;
	countFrame = 0;
}


MegaManAttackState::~MegaManAttackState()
{
}

GameState* MegaManAttackState::onKeyDown(GameObject* gameObject, int keyCode){
	if (keyCode == DIK_D){
		//((MegaMan*)gameObject)->changeAnimation(ECharacter::MEGAMAN, EState::IDLE_FIRE);

		// Thêm viên đạn vào activeObject
		map<int, GameObject*> &activeObject = ObjectManager::getInstance()->getActiveObject();
		GameObject* megaManBullet = ObjectFactory::createObject(ECharacter::MEGAMAN_BULLET);
		megaManBullet->setObjectID(ObjectManager::notInMapObjectId);
		((MegaManBullet*)megaManBullet)->initFire();
		ObjectManager::getInstance()->addObjectToActiveObject(megaManBullet);
		this->isFinishAttack = false;
		ObjectManager::notInMapObjectId++;
	}
	return NULL;
}
GameState*  MegaManAttackState::onKeyUp(GameObject* gameObject, int keyCode){
	if (keyCode == DIK_D){
		//((MegaMan*)gameObject)->changeAnimation(ECharacter::MEGAMAN, EState::IDLE);

	}
	return NULL;
}
GameState*  MegaManAttackState::processKeyState(GameObject* gameObject, BYTE *keyState){
	return NULL;
}

void MegaManAttackState::update(GameObject* gameObject) {}
void MegaManAttackState::enter(GameObject* gameObject){
	//((MegaMan*)gameObject)->changeAnimation(ECharacter::MEGAMAN, EState::IDLE_FIRE);
	int megaManState = gameObject->getState();
	if (isFinishAttack){
		if (megaManState == EState::IDLE)
			((MegaMan*)gameObject)->changeAnimation(ECharacter::MEGAMAN, EState::IDLE);
		else if (megaManState == EState::JUMP)
			((MegaMan*)gameObject)->changeAnimation(ECharacter::MEGAMAN, EState::JUMP);
		else if (megaManState == EState::CLIMB)
			((MegaMan*)gameObject)->changeAnimation(ECharacter::MEGAMAN, EState::CLIMB);
		else if (megaManState == EState::RUNNING)
			((MegaMan*)gameObject)->changeAnimation(ECharacter::MEGAMAN, EState::RUNNING);

	}
	else{
		if (megaManState == EState::IDLE)
			((MegaMan*)gameObject)->changeAnimation(ECharacter::MEGAMAN, EState::IDLE_FIRE);
		else if (megaManState == EState::JUMP)
			((MegaMan*)gameObject)->changeAnimation(ECharacter::MEGAMAN, EState::JUMP_FIRE);
		else if (megaManState == EState::CLIMB)
			((MegaMan*)gameObject)->changeAnimation(ECharacter::MEGAMAN, EState::CLIMB_FIRE);
		else if (megaManState == EState::RUNNING)
			((MegaMan*)gameObject)->changeAnimation(ECharacter::MEGAMAN, EState::RUNNING_FIRE);
	}
	

}
GameState* MegaManAttackState::onCollision(GameObject* gameObject, GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector) {
	SpriteSpec* currentSpriteSpec = gameObject->getSpriteSpec();

	int staticObjectType = staticObject->getType();
	D3DXVECTOR2 normal = collisionVector;
	
	gameObject->setTimeCollision(collisionTime);
	if (collisionTime > 0.0f && collisionTime < 1.0f){
		gameObject->setNoCollisionWithAll(false);
		((MegaMan*)gameObject)->changeAnimation(ECharacter::MEGAMAN, EState::IDLE);

		/*
		NOTE : Khi xét va chạm, không set vị trí và chạm giữa 2 vật trùng nhau mà phải cho chúng nó lệch nhau ít nhất 1px.
		- Position ở đây là top-left của vật.
		*/
		//vật đi từ trên xuống
		if (normal.x == 0.0f && normal.y == 1.0f)
		{
			//FPOINT newPosition = gameObject->getPosition();
			//switch (staticObject->getType()){
			//	// với static object 
			//case ECharacter::STATIC:
			//case ECharacter::LADDER:
			//	newPosition.y = MEGA_MAN_VIRTUAL_HEIGHT + staticObject->getCollisionBox().y + 1;
			//	gameObject->setPostion(newPosition);
			//	/*
			//	Khi mega man đứng trên mặt đất, có phản lực N triệt tiêu lực hấp dẫn. Do đó có thể coi
			//	gia tốc trọng từng = 0 và v.y = 0;
			//	*/
			//	gameObject->setAcceleration(FPOINT(MEGA_MAN_ACCELERATION_X, 0.0f));
			//	gameObject->setVelocity(FPOINT(gameObject->getVelocity().x, 0.0f));
			//	return NULL;
			//default:
			//	break;
			//}
		}
		// vật đi chuyển từ dưới lên
		else if (normal.x == 0.0f && normal.y == -1.0f)
		{
			//return bottomCollision(gameObject, staticObject);
		}
		// vật đi từ phải sang
		else if (normal.x == 1.0f && normal.y == 0.0f){
			//return rightCollision(gameObject, staticObject);
		}
		else
			// vật đi từ trái sang
		if (normal.x == -1.0f && normal.y == 0.0f){
			//return leftCollision(gameObject, staticObject);
		}
	}
	return NULL;
}