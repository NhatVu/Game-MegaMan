#ifndef _CUTMAN_H_
#define _CUTMAN_H_
#include <d3dx9.h>
#include "../../SFramework/SpriteAndAnimation/AnimationSpec.h"
#include "../../SFramework/SpriteAndAnimation/AnimationManager.h"
#include "../../SFramework/GameObject.h"
#include "../../SFramework/Trace.h"
#include "../MegaManUtilities.h"
#include "../../SFramework/Collision.h"
#include "../../SFramework/Map/ObjectFactory.h"
#include "../../SFramework/Map/ObjectManager.h"
#include "CutManCut.h"

using namespace std;
using namespace s_framework;

#define CUTMAN_VELOCITY_Y 0.45f
#define CUTMAN_VELOCITY_X 0.08f
#define CUTMAN_ACTIVE_DISTANCE 100.0f
#define CUTMAN_JUMPING_DISTANCE 80.0f
#define CUTMAN_VIRTUAL_WIDTH 25.0f
#define CUTMAN_VIRTUAL_HEIGHT 20.0f
/*
	cutman cách megaman < c_jumpnig => jumping
	cutman cách megaman > c_jumpnig => nếu từ jumping chuyển sang thì sẽ có động tác vỗ tay rồi mới chạy running

*/
class CutMan : public GameObject
{
private:
	AnimationSpec *m_animation;
	CutManCut *cutManCut;
	int countFrame;
	int countFrameIdle;
	bool colliseLeftRight;
	bool isRender;
	bool canChangeState;
	bool jumpingCollideBottom;

	void onCollisionIdleState(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector);
	void onCollisionRunningState(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector);
	void onCollisionAttackState(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector);
	void onCollisionBeAttackedState(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector);
	void onCollisionJumpingState(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector);
	void changeToIdle();
	void changeToRun();
	void changeToJump();

	void createAttack();
	void returnCutIdle(); // gọi hàm này => cái kéo sẽ nằm trên đầu cutman
public:
	CutMan();
	~CutMan();

	void render() override;
	void onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector)override;
	void updatePosition()override;
	void calculateCollisionBox()override;
	void setState(int state)override;

	void resetToInit()override;
	void die();
};

#endif // !_CUTMAN_H_
