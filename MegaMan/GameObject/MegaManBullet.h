#ifndef _MEGAMAN_BULLET_
#define _MEGAMAN_BULLET_
#include <d3dx9.h>
#include "../../SFramework/SpriteAndAnimation/AnimationSpec.h"
#include "../../SFramework/GameObject.h"
#include "../../SFramework/Trace.h"
#include "../MegaManUtilities.h"
#include "../../SFramework/Collision.h"

using namespace std;
using namespace s_framework;

class MegaManBullet : public GameObject
{

private:
	AnimationSpec* m_animation = NULL;
	EState state;
public:
	MegaManBullet();
	~MegaManBullet();

	/*
	Override
	*/
	void render() override;
	void onKeyDown(int keyCode) override;
	void onKeyUp(int keyCode) override;

	//void updateKeyboard(int keyCode)override;
	void processKeyState(BYTE *keyState)override;
	void onCollision(GameObject* staticObject)override;
	void updatePosition()override;
};


#endif // !_MEGAMAN_BULLET_
