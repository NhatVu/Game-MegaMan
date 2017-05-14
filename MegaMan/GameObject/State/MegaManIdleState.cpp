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
		return new MegaManJumpingState();
	}
	else if (gameObject->getCanClimb() && keyCode == DIK_UP ){
		//gameObject->setVelocity(FPOINT(0.0f, MEGA_MAN_CLIMB_VELOCITY));

		return new MegaManClimbingState();
	}
	else if (gameObject->getCanClimb() && keyCode == DIK_DOWN){
		//gameObject->setVelocity(FPOINT(0.0f, -MEGA_MAN_CLIMB_VELOCITY));
		return new MegaManClimbingState();
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
		if (collisionTime == 0.0f)
			gameObject->setCanClimb(false);
		else gameObject->setCanClimb(true);
		// neu megaman botton < ladder bottom hoac megaman top > ladder top => co gia toc trong tuong
		//if ((gameObject->getPosition().x - MEGA_MAN_VIRTUAL_HEIGHT < staticObject->getPosition().x - staticObject->getHeight()) || gameObject->getPosition().x > staticObject->getPosition().x)
		//{
		//	gameObject->setAcceleration(FPOINT(0.0f, GRAVITATIONAL_ACCELERATION));
		//}
		//else {
		//	//gameObject->setAcceleration(FPOINT())
		//	gameObject->setAcceleration(FPOINT(0.0f, 0.0f));

		//}
	}
	return NULL;
}

GameState* MegaManIdleState::topCollision(GameObject* gameObject, GameObject* staticObject){
	FPOINT newPosition = gameObject->getPosition();
	switch (staticObject->getType()){
		// với static object 
	case ECharacter::STATIC:
	case ECharacter::LADDER:

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

	default:
		break;
	}
	return NULL;
}
GameState* MegaManIdleState::bottomCollision(GameObject* gameObject, GameObject* staticObject){
	return NULL;
}
GameState* MegaManIdleState::leftCollision(GameObject* gameObject, GameObject* staticObject){
	return NULL;
}
GameState* MegaManIdleState::rightCollision(GameObject* gameObject, GameObject* staticObject){
	return NULL;
}
