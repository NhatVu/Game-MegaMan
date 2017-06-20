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
#define MEGA_MAN_VIRTUAL_WIDTH 20.0f
#define MEGA_MAN_VIRTUAL_HEIGHT 20.0f

using namespace s_framework;
/*
	Có 3 trạng thái chính: Đứng(vỗ tay), chạy và nhảy. Trạng thái tấn công xen kẽ giữa 3 trạng thái này, có thể là sau vài giây thì sẽ tấn công 1 lần.

	- Nếu xa hơn 1 khoảng distance => cutman chạy hoặc random cho nó vỗ tay. ít lại.
	- Nếu nhỏ hơn 1 khoảng distnace => cutman nhảy

*/
class MegaMan : public GameObject
{
public:
	MegaMan();
	~MegaMan();

private: 
	AnimationSpec* m_animation = NULL;
	GameState *m_state;
	GameState *m_state_attack;

public:
	bool canChangeViewportUp;
	void setTexture(LPDIRECT3DTEXTURE9 texture);
	virtual void processInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	void changeAnimation(int character, int state);
	void setState(GameState* state){
		m_state = state;
		m_state->enter(this);
	}

	void setState(int eState)override{
		GameObject::setState(eState);
	}

	/*
		Override
	*/
	void render() override;
	void onKeyDown(int keyCode) override;
	void onKeyUp(int keyCode) override;

	//void updateKeyboard(int keyCode)override;
	void processKeyState(BYTE *keyState)override;
	void onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector)override;
	void calculateCollisionBox()override;
	void updatePosition()override;
};

#endif // !_MEGA_MAN_H_



