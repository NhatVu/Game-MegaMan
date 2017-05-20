#include "MegaManIdleState.h"
#include "MegaManRunningState.h"
#include "../MegaMan.h"
#include "../../../SFramework/GameTime.h"
#include "MegaManClimbingState.h"
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
GameState*  MegaManIdleState::onKeyUp(GameObject* gameObject, int keyCode){ return NULL; }
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

}

GameState* MegaManIdleState::onCollision(GameObject* gameObject, GameObject* staticObject) {
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
	if (staticObjectType == ECharacter::LADDER){

		if (collisionTime != 0.0f && (gameObject->getPosition().x + MEGA_MAN_VIRTUAL_WIDTH / 2 > staticObject->getCollisionBox().x + staticObject->getCollisionBox().width / 5)
			&& (gameObject->getPosition().x + MEGA_MAN_VIRTUAL_WIDTH / 2 < staticObject->getCollisionBox().x + 4 * staticObject->getCollisionBox().width / 5)){
			gameObject->setNoCollisionWithAll(false);
			FPOINT newPosition = gameObject->getPosition();
			newPosition.x = staticObject->getCollisionBox().x + staticObject->getCollisionBox().width / 2 - MEGA_MAN_VIRTUAL_WIDTH / 2;
			gameObject->setPostion(newPosition);
			gameObject->setCanClimb(true);

		}
		else
			gameObject->setCanClimb(false);

	}
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
		if ((gameObject->getPosition().x + MEGA_MAN_VIRTUAL_WIDTH / 2 > staticObject->getCollisionBox().x + staticObject->getCollisionBox().width / 5)
			&& (gameObject->getPosition().x + MEGA_MAN_VIRTUAL_WIDTH / 2 < staticObject->getCollisionBox().x + 4 * staticObject->getCollisionBox().width / 5)){
			newPosition.x = staticObject->getCollisionBox().x + staticObject->getCollisionBox().width / 2 - MEGA_MAN_VIRTUAL_WIDTH / 2;

			gameObject->setCanClimb(true);
		}
		else{
			gameObject->setCanClimb(false);

		}
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
