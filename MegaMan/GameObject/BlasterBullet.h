#ifndef _BLASTER_BULLET_H_
#define _BLASTER_BULLET_H_
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
#define BLASTER_BULLET_VELOCITY_X 0.1f

class BlasterBullet : public GameObject
{
private:
	AnimationSpec* m_animation = NULL;
	int countFrame;
public:
	BlasterBullet();
	~BlasterBullet();

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