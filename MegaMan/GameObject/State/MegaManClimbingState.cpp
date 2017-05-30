#include "MegaManClimbingState.h"
#include "../MegaMan.h"
#include "../../../SFramework/GameTime.h"
#include "MegaManJumpingState.h"
#include "../../../SFramework/Camera/ViewPort.h"
#include "MegaManBeAttackedState.h"
#include <vector>

using namespace std;
#define MEGA_MAN_CLIMB_VELOCITY 0.25f
MegaManClimbingState::MegaManClimbingState()
{
	this->name = "Climbing";
	this->canTransitToIdle = false;
	this->isPressDown = false;
}


MegaManClimbingState::~MegaManClimbingState()
{


}

GameState* MegaManClimbingState::onKeyDown(GameObject* gameObject, int keyCode){
	GameState::onKeyDown(gameObject, keyCode);

	if (keyCode == DIK_F){
		gameObject->setVelocity(FPOINT(0.0f, MEGA_MAN_JUMP_VELOCITY));
		return new MegaManJumpingState();
	}
	return NULL;
}
GameState*  MegaManClimbingState::onKeyUp(GameObject* gameObject, int keyCode){
	if (keyCode == DIK_UP || keyCode == DIK_DOWN)
	{
		gameObject->setStopUpdateAnimation(true);
		gameObject->setVelocity(FPOINT(0.0f, 0.0f));
		gameObject->setAcceleration(FPOINT(0.0f, 0.0f));
	}
	return NULL;
}
GameState*  MegaManClimbingState::processKeyState(GameObject* gameObject, BYTE *keyState){
	//GameState::processKeyState(gameObject, keyState);

	//GameState::processKeyState(gameObject, keyState);
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
	gameObject->setState(EState::CLIMB);
}
GameState* MegaManClimbingState::onCollision(GameObject* gameObject, GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector) {

	int staticObjectType = staticObject->getType();
	D3DXVECTOR2 normal = collisionVector;

	//float collisionTime = Collision::CheckCollision(gameObject, staticObject, normal);
	gameObject->setNoCollisionWithAll(false);
	gameObject->setTimeCollision(collisionTime);
	if (collisionTime > 0.0f && collisionTime < 1.0f){
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


	if (staticObjectType == ECharacter::LADDER){
		// kiểm tra xem megaman có thể leo được hay không. 
		((MegaMan*)gameObject)->canChangeViewportUp = false;
		//float megaManCenter = gameObject->getPosition().x + MEGA_MAN_VIRTUAL_WIDTH / 2;
		
		if (collisionTime == 1.0f){
			gameObject->setCanClimb(true);
			FPOINT newPosition = gameObject->getPosition();
			newPosition.x = staticObject->getCollisionBox().x;
			//vì hình cắt bị dư 1 khoảng trống nên phải trừ khi flip trái phải
			if (gameObject->getFlipVertical() == -1)
				newPosition.x -= (gameObject->getSpriteSpec()->getWidth() - MEGA_MAN_VIRTUAL_WIDTH + 5);

			gameObject->setPostion(newPosition);
			if (staticObject->getCollisionBox().y > ViewPort::getInstance()->getViewportBoundary().y)
				((MegaMan*)gameObject)->canChangeViewportUp = true;
		}
		else{
			gameObject->setCanClimb(false);
			return NULL;
		}

		BOX staticCollisonBox = staticObject->getCollisionBox();
		// neu megaman botton < ladder bottom hoac megaman top > ladder top => co gia toc trong tuong
		gameObject->setAcceleration(FPOINT(0.0f, 0.0f));

		// nếu tâm của mega man (trục y) > cầu thang.y => ta chuyển luôn mega man về trạng thái idle. 
		if (gameObject->getPosition().y - MEGA_MAN_VIRTUAL_HEIGHT / 2 > staticCollisonBox.y){
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
			((MegaMan*)gameObject)->canChangeViewportUp = false;
			return new MegaManIdleState();
		}
		else if (gameObject->getPosition().y - MEGA_MAN_VIRTUAL_HEIGHT / 2 < staticCollisonBox.y - staticCollisonBox.height){
			((MegaMan*)gameObject)->canChangeViewportUp = false;
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
		((MegaMan*)gameObject)->canChangeViewportUp = false;
		gameObject->setStopUpdateAnimation(false);
		return new MegaManIdleState();
		break;
	case ECharacter::LADDER:
		if (isPressDown){
			newPosition.y = staticObject->getCollisionBox().y + MEGA_MAN_VIRTUAL_HEIGHT / 2;
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
			gameObject->setStopUpdateAnimation(false);
			((MegaMan*)gameObject)->canChangeViewportUp = false;
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
GameState* MegaManClimbingState::rightCollision(GameObject* gameObject, GameObject* staticObject){
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