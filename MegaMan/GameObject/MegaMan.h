#ifndef _MEGA_MAN_H_
#define _MEGA_MAN_H_

#include <d3dx9.h>
#include "../../SFramework/SpriteAndAnimation/AnimationSpec.h"
#include "../../SFramework/GameObject.h"
#include "../../SFramework/Trace.h"
#include "../MegaManUtilities.h"
#include "../../SFramework/Collision.h"

#include <vector>

#define MEGA_MAN_VELOCITY_X 0.08f
#define MEGA_MAN_VELOCITY_Y -0.03f
#define MEGA_MAN_ACCELERATION_X 0.0f

using namespace s_framework;
class MegaMan : public GameObject
{
public:
	MegaMan();
	~MegaMan();

private: 
	AnimationSpec* m_animation = NULL;
	void resetVelocityAndAcceleration();

public:
	void setTexture(Texture* texture);
	virtual void processInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	void changeAnimation(int character, int state);


	/*
		Override
	*/
	void render() override;
	void onKeyDown(int keyCode) override;
	void onKeyUp(int keyCode) override;

	//void updateKeyboard(int keyCode)override;
	void processKeyState(BYTE *keyState)override;
	void onCollision(GameObject* staticObject)override;
};

#endif // !_MEGA_MAN_H_



