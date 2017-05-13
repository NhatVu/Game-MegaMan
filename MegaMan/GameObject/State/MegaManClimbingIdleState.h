#ifndef _MEGAMAN_CLIMBING_IDLE_STATE_
#define _MEGAMAN_CLIMBING_IDLE_STATE_
#include "GameState.h"
class MegaManClimbingIdleState : public GameState
{
public:
	MegaManClimbingIdleState();
	~MegaManClimbingIdleState();

	GameState* onKeyDown(GameObject* gameObject, int keyCode)override;
	GameState*  onKeyUp(GameObject* gameObject, int keyCode)override;
	GameState*  processKeyState(GameObject* gameObject, BYTE *keyState)override;

	void update(GameObject* gameObject) override;
	void enter(GameObject* gameObject)override;
	GameState* onCollision(GameObject* gameObject, GameObject* staticObject) override;
};

#endif // !_MEGAMAN_CLIMBING_IDLE_STATE_
