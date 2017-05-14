#include "MegaManClimbingIdleState.h"
#include "../MegaMan.h"
#include "../../../SFramework/GameTime.h"
#include "MegaManClimbingState.h"

MegaManClimbingIdleState::MegaManClimbingIdleState()
{
	this->name = "MegaManClimbingIdleState";
}


MegaManClimbingIdleState::~MegaManClimbingIdleState()
{
}

GameState* MegaManClimbingIdleState::onKeyDown(GameObject* gameObject, int keyCode){
	if (keyCode == DIK_UP || keyCode == DIK_DOWN)
		return new MegaManClimbingState();

	return NULL;
}
GameState*  MegaManClimbingIdleState::onKeyUp(GameObject* gameObject, int keyCode){
	return NULL;
}
GameState*  MegaManClimbingIdleState::processKeyState(GameObject* gameObject, BYTE *keyState){
	return NULL;
}

void MegaManClimbingIdleState::update(GameObject* gameObject) {}
void MegaManClimbingIdleState::enter(GameObject* gameObject){
	((MegaMan*)gameObject)->changeAnimation(ECharacter::MEGAMAN, EState::CLIMB_IDLE);

	gameObject->setVelocity(FPOINT(0.0f, 0.0f));
//	gameObject->setAcceleration(FPOINT(0.0f, 0.0f));
}
GameState* MegaManClimbingIdleState::onCollision(GameObject* gameObject, GameObject* staticObject) {
	if (staticObject->getType() == ECharacter::LADDER){

	gameObject->setVelocity(FPOINT(0.0f, 0.0f));
	gameObject->setAcceleration(FPOINT(0.0f, 0.0f));
	}
	return NULL;
}
