#include "GameState.h"
#include "../MegaMan.h"

GameState::GameState()
{
}


GameState::~GameState()
{
}

GameState* GameState::onKeyDown(GameObject* gameObject, int keyCode){
	if (keyCode == DIK_RIGHT){
		gameObject->setFlipVertical(1);
	}

	else if (keyCode == DIK_LEFT){
		gameObject->setFlipVertical(-1);
	}
	return NULL;
}

GameState*  GameState::processKeyState(GameObject* gameObject, BYTE *keyState) {
	if ((keyState[DIK_RIGHT] * 0x80) > 0)
		gameObject->setFlipVertical(1);
	else if ((keyState[DIK_LEFT] * 0x80) > 0)
		gameObject->setFlipVertical(-1);

	return NULL;
}

