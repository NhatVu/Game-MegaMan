#ifndef _MEGAMAN_RUNNING_STATE_H_
#define _MEGAMAN_RUNNING_STATE_H_

#include "GameState.h"
class MegaManRunningState : public GameState
{
public:
	MegaManRunningState();
	~MegaManRunningState();

	GameState* onKeyDown(GameObject* gameObject, int keyCode)override;
	GameState*  onKeyUp(GameObject* gameObject, int keyCode)override;
	GameState*  processKeyState(GameObject* gameObject, BYTE *keyState)override;

	void update(GameObject* gameObject) override;
	void enter(GameObject* gameObject)override;
	GameState* onCollision(GameObject* gameObject, GameObject* staticObject) override;
};

#endif // !_MEGAMAN_RUNNING_STATE_H_



