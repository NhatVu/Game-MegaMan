#ifndef _MAGAMAN_CLIMBING_STATE_
#define _MAGAMAN_CLIMBING_STATE_
#include "GameState.h"
class MegaManClimbingState : public GameState
{
public:
	MegaManClimbingState();
	~MegaManClimbingState();
	GameState* onKeyDown(GameObject* gameObject, int keyCode)override;
	GameState*  onKeyUp(GameObject* gameObject, int keyCode)override;
	GameState*  processKeyState(GameObject* gameObject, BYTE *keyState)override;

	void update(GameObject* gameObject) override;
	void enter(GameObject* gameObject)override;
	GameState* onCollision(GameObject* gameObject, GameObject* staticObject) override;
private:
	GameState* topCollision(GameObject* gameObject, GameObject* staticObject);
	GameState* bottomCollision(GameObject* gameObject, GameObject* staticObject);
	GameState* leftCollision(GameObject* gameObject, GameObject* staticObject);
	GameState* rightCollision(GameObject* gameObject, GameObject* staticObject);

	bool canTransitToIdle;
};

#endif