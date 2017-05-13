#include "MegaManClimbingIdleState.h"
#include "../MegaMan.h"
#include "../../../SFramework/GameTime.h"
#include "MegaManClimbingState.h"

MegaManClimbingIdleState::MegaManClimbingIdleState()
{
}


MegaManClimbingIdleState::~MegaManClimbingIdleState()
{
}

GameState* MegaManClimbingIdleState::onKeyDown(GameObject* gameObject, int keyCode){

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

}
GameState* MegaManClimbingIdleState::onCollision(GameObject* gameObject, GameObject* staticObject) {

	return NULL;
}
