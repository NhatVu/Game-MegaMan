#ifndef _SCREW_H_
#define _SCREW_H_

#include <d3dx9.h>
#include "../../SFramework/SpriteAndAnimation/AnimationSpec.h"
#include "../../SFramework/SpriteAndAnimation/AnimationManager.h"
#include "../../SFramework/GameObject.h"
#include "../../SFramework/Trace.h"
#include "../MegaManUtilities.h"
#include "../../SFramework/Collision.h"
#include "../../SFramework/SFramework.h"
#include "ScrewBullet.h"
using namespace std;
using namespace s_framework;

#define SCREW_FORCE_ATTACK_DISTANCE 70.0f
#define SCREW_VIRTUAL_WIDTH 14.0f
#define SCREW_VIRTUAL_HEIGHT 12.0f

/*
	Trạng thái active, bắn 2 đợt đạn. mỗi đợt cách nhau 0.5s
	- Sau đó trở về trạng thái IDLE -> trong 2s.
	ĐIều kiện, khoảng cách từ megamn tới screw < khoảng A => active
*/
class Screw : public GameObject
{
private:
	AnimationSpec* m_animation = NULL;
	int countFrame;
	bool canAttack;
	void createScrewBullet(float vx, float vy);
	void createAttack();
	bool isRender;
public:
	Screw();
	~Screw();

	void render() override;

	void onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector)override;
	void updatePosition()override;
	void calculateCollisionBox()override;
	void setState(int state)override;

	void resetToInit()override;
	void die();
};

#endif // !_SCREW_H_
