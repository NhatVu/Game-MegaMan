﻿#include "MegaManJumpingState.h"
#include "MegaManRunningState.h"
#include "../MegaMan.h"
#include "../../../SFramework/GameTime.h"

MegaManJumpingState::MegaManJumpingState()
{
}


MegaManJumpingState::~MegaManJumpingState()
{
}

GameState* MegaManJumpingState::onKeyDown(GameObject* gameObject, int keyCode){
	// phim F = fly
	//if (keyCode == DIK_F)

	return NULL;
}
GameState*  MegaManJumpingState::onKeyUp(GameObject* gameObject, int keyCode){ return NULL; }
GameState*  MegaManJumpingState::processKeyState(GameObject* gameObject, BYTE *keyState){
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

	// khi bắt đầu trạng thái jump, ta cấp cho vật thể vận tốc ban đầu. 
	gameObject->setVelocity(FPOINT(0.0f, MEGA_MAN_JUMP_VELOCITY));
}

GameState* MegaManJumpingState::onCollision(GameObject* gameObject, GameObject* staticObject) {
	SpriteSpec* currentSpriteSpec = gameObject->getSpriteSpec();

	int staticObjectType = staticObject->getType();
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	FPOINT velocity = gameObject->getVelocity();
	velocity.x += gameObject->getAcceleration().x*deltaTime;
	velocity.y += gameObject->getAcceleration().y*deltaTime;
	//gameObject->setVelocity(velocity);


	D3DXVECTOR2 normal;

	// set Collision BOX for mega man. 
	BOX collisionBox(gameObject->getPosition().x, gameObject->getPosition().y, MEGA_MAN_VIRTUAL_WIDTH,
		MEGA_MAN_VIRTUAL_HEIGHT, velocity.x * deltaTime, velocity.y*deltaTime);
	gameObject->setCollisionBox(collisionBox);

	// collision
	float collisionTime = Collision::CheckCollision(gameObject, staticObject, normal);
	if (collisionTime > 0.0f && collisionTime < 1.0f){
		/*
		NOTE : Khi xét va chạm, không set vị trí và chạm giữa 2 vật trùng nhau mà phải cho chúng nó lệch nhau ít nhất 1px.
		- Position ở đây là top-left của vật.
		*/
		//vật đi từ trên xuống
		if (normal.x == 0.0f && normal.y == 1.0f)
		{
			FPOINT newPosition = gameObject->getPosition();
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
		// vật đi chuyển từ dưới lên
		else if (normal.x == 0.0f && normal.y == -1.0f)
		{
			FPOINT newPosition = gameObject->getPosition();
			newPosition.y = staticObject->getCollisionBox().y  - staticObject->getCollisionBox().height - 1;
			gameObject->setPostion(newPosition);

			gameObject->setVelocity(FPOINT(gameObject->getVelocity().x, -gameObject->getVelocity().y));
			return new MegaManIdleState();
		}
		// vật đi từ phải sang
		else if (normal.x == 1.0f && normal.y == 0.0f){
			FPOINT newPosition = gameObject->getPosition();
			newPosition.x = staticObject->getCollisionBox().x + staticObject->getCollisionBox().width + 1;
			gameObject->setPostion(newPosition);
			gameObject->setVelocity(FPOINT(-gameObject->getVelocity().x, 0.0f));
			if (staticObject->getType() == 1){
				// va chạm với tường 

			}
			
		}
		else
			// vật đi từ trái sang
		if (normal.x == -1.0f && normal.y == 0.0f){
			FPOINT newPosition = gameObject->getPosition();
			newPosition.x = staticObject->getCollisionBox().x - MEGA_MAN_VIRTUAL_WIDTH - 1;
			gameObject->setPostion(newPosition);

			gameObject->setVelocity(FPOINT(-gameObject->getVelocity().x, 0.0f));
		}
	}
	return NULL;
}
