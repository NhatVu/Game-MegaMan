#ifndef _MEGA_MAN_H_
#define _MEGA_MAN_H_

#include <d3dx9.h>
#include "../../SFramework/SpriteAndAnimation/AnimationSpec.h"
#include "../../SFramework/GameObject.h"
#include "../../SFramework/Trace.h"
#include "../MegaManUtilities.h"
#include "../../SFramework/Collision.h"
#include "State/GameState.h"
#include "State/MegaManIdleState.h"
#include "State/MegaManRunningState.h"
#include <vector>

#define MEGA_MAN_VELOCITY_X 0.15f
#define MEGA_MAN_ACCELERATION_X 0.0f
#define MEGA_MAN_VIRTUAL_WIDTH 22.0f
#define MEGA_MAN_VIRTUAL_HEIGHT 22.0f

using namespace s_framework;
class MegaMan : public GameObject
{
public:
	MegaMan();
	~MegaMan();

private: 
	AnimationSpec* m_animation = NULL;
	GameState *m_state;

public:
	void setTexture(Texture* texture);
	virtual void processInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	void changeAnimation(int character, int state);
	void setState(GameState* state){
		m_state = state;
		m_state->enter(this);
	}

	void setState(EState eState){
		if (eState == EState::IDLE){
			m_state = new MegaManIdleState();
		}
		m_state->enter(this);
	}

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

#endif // !_MEGA_MAN_H_



