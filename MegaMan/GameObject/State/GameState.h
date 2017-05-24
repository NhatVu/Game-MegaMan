#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_
#include "../../../SFramework/GameObject.h"
#include "../../MegaManUtilities.h"
#include <dinput.h>
#include <string>
using namespace s_framework;
using namespace std;
class GameState
{
public:
	GameState();
	
	// handle input
	virtual GameState* onKeyDown(GameObject* gameObject, int keyCode);
	virtual GameState*  onKeyUp(GameObject* gameObject, int keyCode)=0;
	virtual GameState*  processKeyState(GameObject* gameObject, BYTE *keyState)=0;

	virtual void update(GameObject* gameObject) {}
	virtual void enter(GameObject* gameObject){} // không được đụng chạm j hết gia tốc 
	virtual GameState* onCollision(GameObject* gameObject, GameObject* staticObject)=0;
	//virtual void exit(GameObject* gameObject){}
	~GameState();
	string name;
};
#endif // _GAMESTATE_H_



