#include "MegaManClimbingState.h"
#include "../MegaMan.h"
#include "../../../SFramework/GameTime.h"
#include "MegaManClimbingIdleState.h"

#define MEGA_MAN_CLIMB_VELOCITY 0.45f
MegaManClimbingState::MegaManClimbingState()
{
}


MegaManClimbingState::~MegaManClimbingState()
{
}

GameState* MegaManClimbingState::onKeyDown(GameObject* gameObject, int keyCode){

	return NULL;
}
GameState*  MegaManClimbingState::onKeyUp(GameObject* gameObject, int keyCode){

	return NULL;
}
GameState*  MegaManClimbingState::processKeyState(GameObject* gameObject, BYTE *keyState){
	return NULL;
}

void MegaManClimbingState::update(GameObject* gameObject) {}
void MegaManClimbingState::enter(GameObject* gameObject){
	((MegaMan*)gameObject)->changeAnimation(ECharacter::MEGAMAN, EState::CLIMB);

}
GameState* MegaManClimbingState::onCollision(GameObject* gameObject, GameObject* staticObject) {
	return NULL;
}
GameState* MegaManClimbingState::topCollision(GameObject* gameObject, GameObject* staticObject){
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