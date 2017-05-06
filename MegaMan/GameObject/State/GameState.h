#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_
#include "../../../SFramework/GameObject.h"
#include "../../MegaManUtilities.h"
#include <dinput.h>
using namespace s_framework;
class GameState
{
public:
	GameState();
	
	// handle input
	virtual GameState* onKeyDown(GameObject* gameObject, int keyCode)=0;
	virtual GameState*  onKeyUp(GameObject* gameObject, int keyCode)=0;
	virtual GameState*  processKeyState(GameObject* gameObject, BYTE *keyState)=0;

	virtual void update(GameObject* gameObject) {}
	virtual void enter(GameObject* gameObject){}
	virtual GameState* onCollision(GameObject* gameObject, GameObject* staticObject)=0;
	//virtual void exit(GameObject* gameObject){}
	~GameState();
};
#endif // _GAMESTATE_H_


