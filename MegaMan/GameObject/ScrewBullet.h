#ifndef _SCREW_BULLET_H_
#define _SCREW_BULLET_H_
#include <d3dx9.h>
#include "../../SFramework/SpriteAndAnimation/AnimationSpec.h"
#include "../../SFramework/SpriteAndAnimation/AnimationManager.h"
#include "../../SFramework/GameObject.h"
#include "../../SFramework/Trace.h"
#include "../MegaManUtilities.h"
#include "../../SFramework/Collision.h"
#include "../../SFramework/SFramework.h"

using namespace std;
using namespace s_framework;
#define SCREW_BULLET_VELOCITY_X 0.25f

class ScrewBullet : public GameObject
{
	AnimationSpec* m_animation = NULL;
	int countFrame;
public:
	ScrewBullet();
	~ScrewBullet();

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

#endif