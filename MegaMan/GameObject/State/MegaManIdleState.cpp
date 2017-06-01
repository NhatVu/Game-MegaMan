#include "MegaManIdleState.h"
#include "MegaManRunningState.h"
#include "../MegaMan.h"
#include "../../../SFramework/GameTime.h"
#include "MegaManClimbingState.h"
#include "../../../SFramework/Map/ObjectFactory.h"
#include "../../../SFramework/Map/ObjectManager.h"
#include "../MegaManBullet.h"
#include <map>
#include "MegaManAttackState.h"
#include "MegaManBeAttackedState.h"

using namespace std;
MegaManIdleState::MegaManIdleState()
{
	this->name = "Idle";
}


MegaManIdleState::~MegaManIdleState()
{
}

GameState* MegaManIdleState::onKeyDown(GameObject* gameObject, int keyCode){
	GameState::onKeyDown(gameObject, keyCode);
	// keyboard F = Fly
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
GameState*  MegaManIdleState::onKeyUp(GameObject* gameObject, int keyCode){
	if (keyCode == DIK_D){
		//((MegaMan*)gameObject)->changeAnimation(ECharacter::MEGAMAN, EState::IDLE);

	}
	return NULL;
}
GameState*  MegaManIdleState::processKeyState(GameObject* gameObject, BYTE *keyState){
	GameState::processKeyState(gameObject, keyState);
	if ((keyState[DIK_RIGHT] * 0x80) > 0){
		GameState* newState = new MegaManRunningState();
		return newState;
	}

	else if ((keyState[DIK_LEFT] * 0x80) > 0){
		GameState* newState = new MegaManRunningState();
		return newState;
	}
	return NULL;
}

void MegaManIdleState::update(GameObject* gameObject) {}

void MegaManIdleState::enter(GameObject* gameObject){
	// thay đổi animation cho trạng thái idle
	((MegaMan*)gameObject)->changeAnimation(ECharacter::MEGAMAN, EState::IDLE);
	gameObject->setState(EState::IDLE);
}

GameState* MegaManIdleState::onCollision(GameObject* gameObject, GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector) {
	SpriteSpec* currentSpriteSpec = gameObject->getSpriteSpec();
	D3DXVECTOR2 normal = collisionVector;
	int staticObjectType = staticObject->getType();

	gameObject->setTimeCollision(collisionTime);
	if (staticObjectType == ECharacter::LADDER){
		float megaManCenter = gameObject->getPosition().x + MEGA_MAN_VIRTUAL_WIDTH / 2;
		if (gameObject->getFlipVertical() == -1)
			megaManCenter += gameObject->getSpriteSpec()->getWidth() - MEGA_MAN_VIRTUAL_WIDTH;
		if (collisionTime != 0.0f && (megaManCenter> staticObject->getCollisionBox().x + staticObject->getCollisionBox().width / 6)
			&& (megaManCenter < staticObject->getCollisionBox().x + 5.0f * staticObject->getCollisionBox().width / 6)){
			gameObject->setNoCollisionWithAll(false);
			FPOINT newPosition = gameObject->getPosition();
			newPosition.x = staticObject->getCollisionBox().x;
			//vì hình cắt bị dư 1 khoảng trống nên phải trừ khi flip trái phải
			if (gameObject->getFlipVertical() == -1)
				newPosition.x -= gameObject->getSpriteSpec()->getWidth() - MEGA_MAN_VIRTUAL_WIDTH;

			gameObject->setPostion(newPosition);
			gameObject->setCanClimb(true);

		}
		else
			gameObject->setCanClimb(false);

	}
	if (collisionTime > 0.0f && collisionTime < 1.0f){
		gameObject->setNoCollisionWithAll(false);
		((MegaMan*)gameObject)->changeAnimation(ECharacter::MEGAMAN, EState::IDLE);
		// cho những vật chỉ cần va chạm, không cần hướng 
		if (staticObjectType == ECharacter::BLADER || staticObjectType == ECharacter::KAMADOMA
			|| staticObjectType == ECharacter::BLASTER_BULLET || staticObjectType == ECharacter::BLASTER
			|| staticObjectType == ECharacter::SUZY || staticObjectType == ECharacter::SCREW_BULLET){
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

	// xét trong trường hợp collideTime = 1

	return NULL;
}

GameState* MegaManIdleState::topCollision(GameObject* gameObject, GameObject* staticObject){
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
		return NULL;
		//break
	case ECharacter::LADDER:
		//trong tạng thái nghỉ, mega man va chạm top với ladder, nếu dk về x không thỏa mãn
		// không thể leo xuống được. canClimb = false;

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
GameState* MegaManIdleState::bottomCollision(GameObject* gameObject, GameObject* staticObject){
	return NULL;
}
GameState* MegaManIdleState::leftCollision(GameObject* gameObject, GameObject* staticObject){
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
GameState* MegaManIdleState::rightCollision(GameObject* gameObject, GameObject* staticObject){
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
