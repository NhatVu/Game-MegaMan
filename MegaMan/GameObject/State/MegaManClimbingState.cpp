﻿#include "MegaManClimbingState.h"
#include "../MegaMan.h"
#include "../../../SFramework/GameTime.h"
#include "MegaManJumpingState.h"

#define MEGA_MAN_CLIMB_VELOCITY 0.25f
MegaManClimbingState::MegaManClimbingState()
{
	this->name = "MegaManClimbingState";
	this->canTransitToIdle = false;
	this->isPressDown = false;
	this->canChangeToNextViewport = false;
	this->canChangeToPreviousViewport = false;
}


MegaManClimbingState::~MegaManClimbingState()
{
	

}

GameState* MegaManClimbingState::onKeyDown(GameObject* gameObject, int keyCode){
	if (keyCode == DIK_F){
		return new MegaManJumpingState();
	}

	if (gameObject->getCanClimb() && (keyCode == DIK_UP || keyCode == DIK_DOWN)){
		//((MegaMan*)gameObject)->changeAnimation(ECharacter::MEGAMAN, EState::CLIMB);
	}
	return NULL;
}
GameState*  MegaManClimbingState::onKeyUp(GameObject* gameObject, int keyCode){
	if (keyCode == DIK_UP || keyCode == DIK_DOWN)
	{
		//((MegaMan*)gameObject)->changeAnimation(ECharacter::MEGAMAN, EState::CLIMB_IDLE);
		gameObject->setStopUpdateAnimation(true);
		gameObject->setVelocity(FPOINT(0.0f, 0.0f));
		gameObject->setAcceleration(FPOINT(0.0f, 0.0f));
	}
	return NULL;
}
GameState*  MegaManClimbingState::processKeyState(GameObject* gameObject, BYTE *keyState){
	GameState::processKeyState(gameObject, keyState);
	if (gameObject->getCanClimb() && (keyState[DIK_UP] * 0x80) > 0){
		gameObject->setStopUpdateAnimation(false);
		gameObject->setVelocity(FPOINT(0.0f, MEGA_MAN_CLIMB_VELOCITY));
	}
	else if (gameObject->getCanClimb() && (keyState[DIK_DOWN] * 0x80) > 0){
		gameObject->setStopUpdateAnimation(false);
		this->isPressDown = true;
		gameObject->setVelocity(FPOINT(0.0f, -MEGA_MAN_CLIMB_VELOCITY));
	}
	return NULL;
}

void MegaManClimbingState::update(GameObject* gameObject) {}
void MegaManClimbingState::enter(GameObject* gameObject){

	((MegaMan*)gameObject)->changeAnimation(ECharacter::MEGAMAN, EState::CLIMB);

}
GameState* MegaManClimbingState::onCollision(GameObject* gameObject, GameObject* staticObject) {
	SpriteSpec* currentSpriteSpec = gameObject->getSpriteSpec();

	int staticObjectType = staticObject->getType();
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	FPOINT velocity = gameObject->getVelocity();
	velocity.x += gameObject->getAcceleration().x*deltaTime;
	velocity.y += gameObject->getAcceleration().y*deltaTime;

	D3DXVECTOR2 normal;

	// set Collision BOX for mega man. 
	BOX collisionBox(gameObject->getPosition().x, gameObject->getPosition().y, MEGA_MAN_VIRTUAL_WIDTH,
		MEGA_MAN_VIRTUAL_HEIGHT, velocity.x * deltaTime, velocity.y*deltaTime);
	gameObject->setCollisionBox(collisionBox);

	// collision

	float collisionTime = Collision::CheckCollision(gameObject, staticObject, normal);
		gameObject->setNoCollisionWithAll(false);
		gameObject->setTimeCollision(collisionTime);
	if (collisionTime > 0.0f && collisionTime < 1.0f){
		/*
		NOTE : Khi xét va chạm, không set vị trí và chạm giữa 2 vật trùng nhau mà phải cho chúng nó lệch nhau ít nhất 1px.
		- Position ở đây là top-left của vật.
		*/
		//vật đi từ trên xuống
		if (normal.x == 0.0f && normal.y == 1.0f)
		{
			return topCollision(gameObject, staticObject);
		}
	}


	if (staticObjectType == ECharacter::LADDER){

		// kiểm tra xem megaman có thể leo được hay không. 
		if (collisionTime == 1.0f)
			gameObject->setCanClimb(true);
		else{
			gameObject->setCanClimb(false);
			return NULL;
		}

		// check xem trong khi đang leo thang có thể chuyển viewport state được hay không 
		
		// neu megaman botton < ladder bottom hoac megaman top > ladder top => co gia toc trong tuong
		gameObject->setAcceleration(FPOINT(0.0f, 0.0f));

		BOX staticCollisonBox = staticObject->getCollisionBox();
		// nếu tâm của mega man (trục y) > cầu thang.y => ta chuyển luôn mega man về trạng thái idle. 
		if (gameObject->getPosition().y - MEGA_MAN_VIRTUAL_HEIGHT / 2 > staticCollisonBox.y
			|| (gameObject->getPosition().y - MEGA_MAN_VIRTUAL_HEIGHT / 2 < staticCollisonBox.y - staticCollisonBox.height)){
			FPOINT newPosition = gameObject->getPosition();

			newPosition.y = MEGA_MAN_VIRTUAL_HEIGHT + staticObject->getCollisionBox().y + 1;
			gameObject->setPostion(newPosition);
			/*
			Khi mega man đứng trên mặt đất, có phản lực N triệt tiêu lực hấp dẫn. Do đó có thể coi
			gia tốc trọng từng = 0 và v.y = 0;
			*/
			gameObject->setAcceleration(FPOINT(MEGA_MAN_ACCELERATION_X, 0.0f));
			gameObject->setVelocity(FPOINT(gameObject->getVelocity().x, 0.0f));
			gameObject->setStopUpdateAnimation(false);
			return new MegaManIdleState();
		}
	}
	return NULL;
}
GameState* MegaManClimbingState::topCollision(GameObject* gameObject, GameObject* staticObject){
	FPOINT newPosition = gameObject->getPosition();
	switch (staticObject->getType()){
		// với static object 
	case ECharacter::STATIC:

		newPosition.y = MEGA_MAN_VIRTUAL_HEIGHT + staticObject->getCollisionBox().y + 1;
		gameObject->setPostion(newPosition);
		/*
		Khi mega man đứng trên mặt đất, có phản lực N triệt tiêu lực hấp dẫn. Do đó có thể coi
		gia tốc trọng từng = 0 và v.y = 0;
		*/
		gameObject->setAcceleration(FPOINT(MEGA_MAN_ACCELERATION_X, 0.0f));
		gameObject->setVelocity(FPOINT(gameObject->getVelocity().x, 0.0f));
		return new MegaManIdleState();
		break;
	case ECharacter::LADDER:
		if (isPressDown){
			newPosition.y = staticObject->getCollisionBox().y + MEGA_MAN_VIRTUAL_HEIGHT/2 ;
			gameObject->setPostion(newPosition);
		}
		else{
			newPosition.y = MEGA_MAN_VIRTUAL_HEIGHT + staticObject->getCollisionBox().y + 1;
			gameObject->setPostion(newPosition);
			/*
			Khi mega man đứng trên mặt đất, có phản lực N triệt tiêu lực hấp dẫn. Do đó có thể coi
			gia tốc trọng từng = 0 và v.y = 0;
			*/
			gameObject->setAcceleration(FPOINT(MEGA_MAN_ACCELERATION_X, 0.0f));
			gameObject->setVelocity(FPOINT(gameObject->getVelocity().x, 0.0f));
			return new MegaManIdleState();
		}
		
		break;

	default:
		break;
	}
	return NULL;
}
GameState* MegaManClimbingState::bottomCollision(GameObject* gameObject, GameObject* staticObject){

	return NULL;
}
GameState* MegaManClimbingState::leftCollision(GameObject* gameObject, GameObject* staticObject){
	return NULL;
}
GameState* MegaManClimbingState::rightCollision(GameObject* gameObject, GameObject* staticObject){
	return NULL;
}