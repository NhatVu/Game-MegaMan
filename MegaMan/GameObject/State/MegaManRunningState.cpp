#include "MegaManRunningState.h"
#include "../MegaMan.h"
#include "../../../SFramework/GameTime.h"
#include "MegaManClimbingState.h"
#include "MegaManBeAttackedState.h"
MegaManRunningState::MegaManRunningState()
{
	this->name = "Running";
}


MegaManRunningState::~MegaManRunningState()
{
}

GameState* MegaManRunningState::onKeyDown(GameObject* gameObject, int keyCode){
	GameState::onKeyDown(gameObject, keyCode);
	if (keyCode == DIK_F)
	{
		gameObject->setVelocity(FPOINT(0.0f, MEGA_MAN_JUMP_VELOCITY));
		return new MegaManJumpingState();
	}
	else if (gameObject->getCanClimb() && keyCode == DIK_UP){
		//gameObject->setVelocity(FPOINT(0.0f, MEGA_MAN_CLIMB_VELOCITY));

		return new MegaManClimbingState();
	}
	else if (gameObject->getCanClimb() == 1 && keyCode == DIK_DOWN){
		//gameObject->setVelocity(FPOINT(0.0f, -MEGA_MAN_CLIMB_VELOCITY));
		GameState* state = new MegaManClimbingState();
		((MegaManClimbingState*)state)->isPressDown = true;
		return state;
	}
	return NULL;
}
GameState*  MegaManRunningState::onKeyUp(GameObject* gameObject, int keyCode){
	if (keyCode == DIK_LEFT || keyCode == DIK_RIGHT)
		return new MegaManIdleState();
	return NULL;
}
GameState*  MegaManRunningState::processKeyState(GameObject* gameObject, BYTE *keyState){
	GameState::processKeyState(gameObject, keyState);
	FPOINT currentPosition = gameObject->getPosition();
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	gameObject->setStopUpdateAnimation(false);
	if ((keyState[DIK_RIGHT] * 0x80) > 0)
	{
		FPOINT velocity = gameObject->getVelocity();
		/*if (velocity.x < 0.0f)
			velocity.x *= -1;
			else if (velocity.x == 0.0f)*/
		velocity.x = MEGA_MAN_VELOCITY_X;
		gameObject->setVelocity(velocity);
	}
	else
	if ((keyState[DIK_LEFT] * 0x80) > 0)
	{
		FPOINT velocity = gameObject->getVelocity();
		/*	if (velocity.x > 0.0f)
				velocity.x *= -1;
				else if (velocity.x == 0.0f)*/
		velocity.x = -MEGA_MAN_VELOCITY_X;
		gameObject->setVelocity(velocity);
	}
	return NULL;
}

void MegaManRunningState::update(GameObject* gameObject) {}
void MegaManRunningState::enter(GameObject* gameObject){
	// change animation for running state
	((MegaMan*)gameObject)->changeAnimation(ECharacter::MEGAMAN, EState::RUNNING);
	gameObject->setState(EState::RUNNING);
}

GameState* MegaManRunningState::onCollision(GameObject* gameObject, GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector) {
	//gameObject->setAcceleration(FPOINT(0.0f, GRAVITATIONAL_ACCELERATION));
	SpriteSpec* currentSpriteSpec = gameObject->getSpriteSpec();
	int staticObjectType = staticObject->getType();
	D3DXVECTOR2 normal = collisionVector;

	gameObject->setTimeCollision(collisionTime);
#pragma region collsion for ladder
	if (staticObjectType == ECharacter::LADDER){
		float megaManCenter = gameObject->getPosition().x + MEGA_MAN_VIRTUAL_WIDTH / 2;
		if (gameObject->getFlipVertical() == -1)
			megaManCenter += gameObject->getSpriteSpec()->getWidth() - MEGA_MAN_VIRTUAL_WIDTH;
		if (collisionTime != 0.0f && (megaManCenter > staticObject->getCollisionBox().x + staticObject->getCollisionBox().width / 6)
			&& (megaManCenter < staticObject->getCollisionBox().x + 5.0f * staticObject->getCollisionBox().width / 6)){
			gameObject->setNoCollisionWithAll(false);
			/*	FPOINT newPosition = gameObject->getPosition();
				newPosition.x = staticObject->getCollisionBox().x + staticObject->getCollisionBox().width / 2 - MEGA_MAN_VIRTUAL_WIDTH / 2;
				if (gameObject->getFlipVertical() == -1)
				newPosition.x -= gameObject->getSpriteSpec()->getWidth() - MEGA_MAN_VIRTUAL_WIDTH;

				gameObject->setPostion(newPosition);*/
			gameObject->setCanClimb(true);

		}
		else
			gameObject->setCanClimb(false);

	}
#pragma endregion

	if (collisionTime > 0.0f && collisionTime < 1.0f){
		gameObject->setNoCollisionWithAll(false);
		/*
		NOTE : Khi xét va chạm, không set vị trí và chạm giữa 2 vật trùng nhau mà phải cho chúng nó lệch nhau ít nhất 1px.
		- Position ở đây là top-left của vật.
		*/

		// cho những vật chỉ cần va chạm, không cần hướng 
		if (staticObjectType == ECharacter::BLADER || staticObjectType == ECharacter::KAMADOMA
			|| staticObjectType == ECharacter::BLASTER_BULLET || staticObjectType == ECharacter::BLASTER
			|| staticObjectType == ECharacter::SUZY){
			FPOINT newPosition = gameObject->getPosition();

			if (newPosition.x > staticObject->getPosition().x)
				newPosition.x += MOVING_X_WHEN_ATTACKED;
			else newPosition.x -= MOVING_X_WHEN_ATTACKED;
			gameObject->setPostion(newPosition);
			return new MegaManBeAttackedState();
		}

		//vật đi từ trên xuống
		if (normal.x == 0.0f && normal.y == 1.0f)
		{
			return topCollision(gameObject, staticObject);
		}
		else
			// vật đi từ trái sang
		if (normal.x == -1.0f && normal.y == 0.0f){
			return leftCollision(gameObject, staticObject);
		}
		// vật đi từ phải sang
		else if (normal.x == 1.0f && normal.y == 0.0f){
			return rightCollision(gameObject, staticObject);
		}

	}
	

	return NULL;
}

GameState* MegaManRunningState::topCollision(GameObject* gameObject, GameObject* staticObject){
	FPOINT newPosition = gameObject->getPosition();
	switch (staticObject->getType()){
	case ECharacter::STATIC:
	case ECharacter::LADDER:
		newPosition.y = MEGA_MAN_VIRTUAL_HEIGHT + staticObject->getCollisionBox().y + 1;
		gameObject->setPostion(newPosition);

		gameObject->setAcceleration(FPOINT(MEGA_MAN_ACCELERATION_X, 0.0f));
		gameObject->setVelocity(FPOINT(gameObject->getVelocity().x, 0.0f));
		break;
	default:
		break;
	}

	
	return NULL;
}
GameState* MegaManRunningState::bottomCollision(GameObject* gameObject, GameObject* staticObject){
	return NULL;
}
GameState* MegaManRunningState::leftCollision(GameObject* gameObject, GameObject* staticObject){
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
GameState* MegaManRunningState::rightCollision(GameObject* gameObject, GameObject* staticObject){
	FPOINT newPosition = gameObject->getPosition();
	switch (staticObject->getType()){
	case ECharacter::STATIC:
		newPosition.x = staticObject->getCollisionBox().x + staticObject->getCollisionBox().width + 1;
		gameObject->setPostion(newPosition);
		gameObject->setVelocity(FPOINT(0.0f, gameObject->getVelocity().y));
		break;
	default: break;
	}
	
	return NULL;
}
