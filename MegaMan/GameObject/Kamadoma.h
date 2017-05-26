#ifndef _KAMADOMA_H_
#define _KAMADOMA_H_
#include <d3dx9.h>
#include "../../SFramework/SpriteAndAnimation/AnimationSpec.h"
#include "../../SFramework/SpriteAndAnimation/AnimationManager.h"
#include "../../SFramework/GameObject.h"
#include "../../SFramework/Trace.h"
#include "../MegaManUtilities.h"
#include "../../SFramework/Collision.h"

using namespace std;
using namespace s_framework;

#define KAMADOMA_VELOCITY_Y 0.45f
#define KAMADOMA_VELOCITY_X 0.07f
#define KAMADOMA_ACTIVE_DISTANCE 100.0f
#define KAMADOMA_FORCE_ATTACK_DISTANCE 70.0f
#define KAMADOMA_VIRTUAL_WIDTH 14.0f
#define KAMADOMA_VIRTUAL_HEIGHT 12.0f
/*
	Nếu khoảng cách từ kamadoma và megaman < 1 số A =>  kamadoma di chuyển bình thường với vx normal
	Nếu khoảng cách > A => kamadoma vx = A/dt để nó di chuyển chạm vào vị trí trước đó của mega man. 

	Khi megaman va chạm với kamadoma thì bị lùi lại 1 ít và flip theo trục y. (đang quay mặt phải => va chạm => quay mặt trái)
*/
class Kamadoma : public GameObject
{
private:
	AnimationSpec* m_animation = NULL;
	EState state;
	bool canAttack;
	bool isLeftCollision = false; // va cham trai voi static
	bool isRightCollision = false;// va cham phai voi static
public:
	Kamadoma();
	~Kamadoma();
	/*
	Override
	*/
	void render() override;
	void onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector)override;
	void updatePosition()override;
	void calculateCollisionBox()override;
	void setState(int state)override;

	void resetToInit()override;
	void die();
};

#endif // !_KAMADOMA_H_
