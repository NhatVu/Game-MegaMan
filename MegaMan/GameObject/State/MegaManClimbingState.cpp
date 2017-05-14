#include "MegaManClimbingState.h"
#include "../MegaMan.h"
#include "../../../SFramework/GameTime.h"
#include "MegaManClimbingIdleState.h"

#define MEGA_MAN_CLIMB_VELOCITY 0.4f
MegaManClimbingState::MegaManClimbingState()
{
}


MegaManClimbingState::~MegaManClimbingState()
{
	this->name = "MegaManClimbingState";
	this->canTransitToIdle = false;

}

GameState* MegaManClimbingState::onKeyDown(GameObject* gameObject, int keyCode){
	if (keyCode == DIK_UP || keyCode == DIK_DOWN){
		((MegaMan*)gameObject)->changeAnimation(ECharacter::MEGAMAN, EState::CLIMB);
	}
	return NULL;
}
GameState*  MegaManClimbingState::onKeyUp(GameObject* gameObject, int keyCode){
	if (keyCode == DIK_UP || keyCode == DIK_DOWN)
		//	return new MegaManClimbingIdleState();
	{
		((MegaMan*)gameObject)->changeAnimation(ECharacter::MEGAMAN, EState::CLIMB_IDLE);
		gameObject->setVelocity(FPOINT(0.0f, 0.0f));
		gameObject->setAcceleration(FPOINT(0.0f, 0.0f));
	}
	return NULL;
}
GameState*  MegaManClimbingState::processKeyState(GameObject* gameObject, BYTE *keyState){
	GameState::processKeyState(gameObject, keyState);
	if (gameObject->getCanClimb() && (keyState[DIK_UP] * 0x80) > 0){
		gameObject->setVelocity(FPOINT(0.0f, MEGA_MAN_CLIMB_VELOCITY));
	}
	else if (gameObject->getCanClimb() && (keyState[DIK_DOWN] * 0x80) > 0){
		gameObject->setVelocity(FPOINT(0.0f, -MEGA_MAN_CLIMB_VELOCITY));
	}
	return NULL;
}

void MegaManClimbingState::update(GameObject* gameObject) {}
void MegaManClimbingState::enter(GameObject* gameObject){
	((MegaMan*)gameObject)->changeAnimation(ECharacter::MEGAMAN, EState::CLIMB);
	gameObject->setVelocity(FPOINT(0.0f, MEGA_MAN_CLIMB_VELOCITY));

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
		if (collisionTime == 1.0f)
			gameObject->setCanClimb(true);
		else
			gameObject->setCanClimb(false);
		// neu megaman botton < ladder bottom hoac megaman top > ladder top => co gia toc trong tuong
		BOX staticCollisonBox = staticObject->getCollisionBox();
		if ((gameObject->getPosition().y - MEGA_MAN_VIRTUAL_HEIGHT < staticCollisonBox.y - staticCollisonBox.height ) || gameObject->getPosition().y > staticCollisonBox.y)
		{
			gameObject->setAcceleration(FPOINT(0.0f, GRAVITATIONAL_ACCELERATION));
			this->canTransitToIdle = true;
		}
		else {
			//gameObject->setAcceleration(FPOINT())
			gameObject->setAcceleration(FPOINT(0.0f, 0.0f));
			this->canTransitToIdle = false;

		}
	}
	return NULL;
}
GameState* MegaManClimbingState::topCollision(GameObject* gameObject, GameObject* staticObject){
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
		if (this->canTransitToIdle)
			return new MegaManIdleState();
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