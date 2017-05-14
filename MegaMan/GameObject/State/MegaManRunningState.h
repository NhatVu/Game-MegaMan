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
private:
	GameState* topCollision(GameObject* gameObject, GameObject* staticObject);
	GameState* bottomCollision(GameObject* gameObject, GameObject* staticObject);
	GameState* leftCollision(GameObject* gameObject, GameObject* staticObject);
	GameState* rightCollision(GameObject* gameObject, GameObject* staticObject);

};

#endif // !_MEGAMAN_RUNNING_STATE_H_



