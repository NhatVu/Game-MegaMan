#include "MegaManRunningState.h"
#include "../MegaMan.h"
#include "../../../SFramework/GameTime.h"

MegaManRunningState::MegaManRunningState()
{
}


MegaManRunningState::~MegaManRunningState()
{
}

GameState* MegaManRunningState::onKeyDown(GameObject* gameObject, int keyCode){
	GameState::onKeyDown(gameObject, keyCode);
	if (keyCode == DIK_F)
	{
		return new MegaManJumpingState();
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
	//gameObject->setVelocity(FPOINT(MEGA_MAN_VELOCITY_X, MEGA_MAN_VELOCITY_Y));
	gameObject->setAcceleration(FPOINT(0.0f, GRAVITATIONAL_ACCELERATION));

}

GameState* MegaManRunningState::onCollision(GameObject* gameObject, GameObject* staticObject) {
	//gameObject->setAcceleration(FPOINT(0.0f, GRAVITATIONAL_ACCELERATION));
	/*SpriteSpec* currentSpriteSpec = m_animation->getCurrentSpriteSpec();
	GameObject::setSpriteSpec(currentSpriteSpec);*/
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
		gameObject->setDetectedCollision(true);
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
		}else
		// vật đi từ trái sang
		if (normal.x == -1.0f && normal.y == 0.0f){
			FPOINT newPosition = gameObject->getPosition();
			newPosition.x = staticObject->getCollisionBox().x - MEGA_MAN_VIRTUAL_WIDTH - 1;
			gameObject->setPostion(newPosition);
			
			gameObject->setVelocity(FPOINT(-gameObject->getVelocity().x, 0.0f));
		}
		// vật đi từ phải sang
		else if (normal.x == 1.0f && normal.y == 0.0f){
			FPOINT newPosition = gameObject->getPosition();
			newPosition.x = staticObject->getCollisionBox().x + staticObject->getCollisionBox().width + 1;
			gameObject->setPostion(newPosition);

			//gameObject->setAcceleration(FPOINT(MEGA_MAN_ACCELERATION_X, GRAVITATIONAL_ACCELERATION));
			// vì chúng ta ko sử dụng gia tốc trục x nên khi va chạm trái phải, ta không set lại gia tốc
			// gia tốc trục y sẽ được giữ của lần xét va chạm trước đó. 
			gameObject->setVelocity(FPOINT(-gameObject->getVelocity().x, 0.0f));
			if (staticObject->getType() == 1){
				// va chạm với tường 

			}
			//gameObject->setVelocity(FPOINT(0.0f, 0.0f));
		}

	}

	return NULL;
}