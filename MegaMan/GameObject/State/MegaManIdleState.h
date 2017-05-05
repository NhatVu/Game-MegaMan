#ifndef _MEGAMAN_IDLE_STATE_H_
#define _MEGAMAN_IDLE_STATE_H_
#include "GameState.h"
class MegaManIdleState : public GameState
{
public:
	MegaManIdleState();
	~MegaManIdleState();

	GameState* onKeyDown(GameObject* gameObject, int keyCode)override;
	GameState*  onKeyUp(GameObject* gameObject, int keyCode)override;
	GameState*  processKeyState(GameObject* gameObject, BYTE *keyState)override;

	void update(GameObject* gameObject) override;
	void enter(GameObject* gameObject)override;
	GameState* onCollision(GameObject* gameObject, GameObject* staticObject) override;

};

#endif // !_MEGAMAN_IDLE_STATE_H



