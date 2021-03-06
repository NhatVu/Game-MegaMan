﻿#include "MegaManJumpingState.h"
#include "MegaManRunningState.h"
#include "../MegaMan.h"
#include "../../../SFramework/GameTime.h"
#include "../../../SFramework/Camera/ViewPort.h"
#include "MegaManClimbingState.h"
#include "MegaManBeAttackedState.h"
MegaManJumpingState::MegaManJumpingState()
{
	this->name = "Jumping";
}


MegaManJumpingState::~MegaManJumpingState()
{
}

GameState* MegaManJumpingState::onKeyDown(GameObject* gameObject, int keyCode){
	// phim F = fly
	GameState::onKeyDown(gameObject, keyCode);
	if (keyCode == DIK_UP || keyCode == DIK_DOWN){
		gameObject->setCanClimb(true);
	}


	return NULL;
}
GameState*  MegaManJumpingState::onKeyUp(GameObject* gameObject, int keyCode){
	if (keyCode == DIK_UP || keyCode == DIK_DOWN){
		gameObject->setCanClimb(false);
	}
	return NULL;
}
GameState*  MegaManJumpingState::processKeyState(GameObject* gameObject, BYTE *keyState){
	GameState::processKeyState(gameObject, keyState);

	if ((keyState[DIK_RIGHT] * 0x80) > 0){
		//GameState* newState = new MegaManRunningState();
		//newState->enter(gameObject);
		//return newState;
		gameObject->setVelocity(FPOINT(MEGA_MAN_VELOCITY_X, gameObject->getVelocity().y));

	}

	else if ((keyState[DIK_LEFT] * 0x80) > 0){
		//GameState* newState = new MegaManRunningState();
		//newState->enter(gameObject);
		//return newState;
		gameObject->setVelocity(FPOINT(-MEGA_MAN_VELOCITY_X, gameObject->getVelocity().y));

	}
	return NULL;
}

void MegaManJumpingState::update(GameObject* gameObject) {}

void MegaManJumpingState::enter(GameObject* gameObject){
	// thay đổi animation cho trạng thái idle
	((MegaMan*)gameObject)->changeAnimation(ECharacter::MEGAMAN, EState::JUMP);
	gameObject->setState(EState::JUMP);
}

GameState* MegaManJumpingState::onCollision(GameObject* gameObject, GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector) {
	SpriteSpec* currentSpriteSpec = gameObject->getSpriteSpec();

	int staticObjectType = staticObject->getType();
	D3DXVECTOR2 normal = collisionVector;
	//gameObject->setCanClimb(false);
	gameObject->setTimeCollision(collisionTime);
	
	// xử lý riêng cho cái cầu thang
	if (gameObject->getCanClimb() && !gameObject->getStopUpdateAnimation() && staticObjectType == ECharacter::LADDER && collisionTime > 0.0f && collisionTime <= 1.0f){
		FPOINT newPosition = gameObject->getPosition();
		newPosition.x = staticObject->getCollisionBox().x;
		if (gameObject->getFlipVertical() == -1)
			newPosition.x -= gameObject->getSpriteSpec()->getWidth() - MEGA_MAN_VIRTUAL_WIDTH;
		gameObject->setPostion(newPosition);
		gameObject->setStopUpdateAnimation(true);
		gameObject->setVelocity(FPOINT(0.0f, 0.0f));
		gameObject->setAcceleration(FPOINT(0.0f, 0.0f));
		gameObject->setCanClimb(false);
		return new MegaManClimbingState();
	}
	if (collisionTime > 0.0f && collisionTime < 1.0f){
		gameObject->setNoCollisionWithAll(false);
		// cho những vật chỉ cần va chạm, không cần hướng 
		if (staticObjectType == ECharacter::BLADER || staticObjectType == ECharacter::KAMADOMA
			|| staticObjectType == ECharacter::BLASTER_BULLET || staticObjectType == ECharacter::BLASTER 
			|| staticObjectType == ECharacter::SUZY || staticObjectType == ECharacter::SCREW_BULLET || staticObjectType == ECharacter::SUPER_CUTTER || staticObjectType == ECharacter::BIG_EYE){
			FPOINT newPosition = gameObject->getPosition();

			if (newPosition.x > staticObject->getPosition().x)
				newPosition.x += MOVING_X_WHEN_ATTACKED;
			else newPosition.x -= MOVING_X_WHEN_ATTACKED;
			gameObject->setPostion(newPosition);
			return new MegaManBeAttackedState();
		}
		/*
		NOTE : Khi xét va chạm, không set vị trí và chạm giữa 2 vật trùng nhau mà phải cho chúng nó lệch nhau ít nhất 1px.
		- Position ở đây là top-left của vật.
		*/
		//vật đi từ trên xuống
		if (normal.x == 0.0f && normal.y == 1.0f)
		{
			return topCollision(gameObject, staticObject);
		}
		// vật đi chuyển từ dưới lên
		else if (normal.x == 0.0f && normal.y == -1.0f)
		{
			return bottomCollision(gameObject, staticObject);
		}
		// vật đi từ phải sang
		else if (normal.x == 1.0f && normal.y == 0.0f){
			return rightCollision(gameObject, staticObject);
		}
		else
			// vật đi từ trái sang
		if (normal.x == -1.0f && normal.y == 0.0f){
			return leftCollision(gameObject, staticObject);
		}
	}
	return NULL;
}

GameState* MegaManJumpingState::topCollision(GameObject* gameObject, GameObject* staticObject){
	FPOINT newPosition = gameObject->getPosition();
	switch (staticObject->getType()){
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
	default:
		break;
	}
	return NULL;
}
GameState* MegaManJumpingState::bottomCollision(GameObject* gameObject, GameObject* staticObject){
	FPOINT newPosition = gameObject->getPosition();
	switch (staticObject->getType()){
	case ECharacter::STATIC:
		newPosition.y = staticObject->getCollisionBox().y - staticObject->getCollisionBox().height - 1;
		gameObject->setPostion(newPosition);
		//Lẽ ra phải là gameObject->getVelocity().y nhưng vì để như vậy, vận tốc quá lớn dẫn đến frame tiếp theo,
		// vật đã bị trùng vào nền => ko xảy ra va chạm theo swapaabb. nên ta bị dội ngược lại cho va chạm với bottom viên gạch, vận tốc lúc này chỉ có gia tốc y sinh ra, không do -vy còn dư thừa.

		gameObject->setVelocity(FPOINT(gameObject->getVelocity().x, 0.0f));
		break;
	default:
		break;
	}

	return NULL;
}
GameState* MegaManJumpingState::leftCollision(GameObject* gameObject, GameObject* staticObject){
	FPOINT newPosition = gameObject->getPosition();
	switch (staticObject->getType()){
	case ECharacter::STATIC:
		newPosition.x = staticObject->getCollisionBox().x - MEGA_MAN_VIRTUAL_WIDTH - 1;
		gameObject->setPostion(newPosition);

		gameObject->setVelocity(FPOINT(0.0f, gameObject->getVelocity().y));
		break;

	default:
		break;
	}

	return NULL;
}
GameState* MegaManJumpingState::rightCollision(GameObject* gameObject, GameObject* staticObject){
	FPOINT newPosition = gameObject->getPosition();
	switch (staticObject->getType()){
	case ECharacter::STATIC:
		newPosition.x = staticObject->getCollisionBox().x + staticObject->getCollisionBox().width + 1;
		gameObject->setPostion(newPosition);
		gameObject->setVelocity(FPOINT(0.0f, gameObject->getVelocity().y));
		break;

	default:
		break;
	}

	return NULL;
}