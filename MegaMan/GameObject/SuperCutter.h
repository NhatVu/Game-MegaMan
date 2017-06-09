#ifndef _SUPER_CUTTER_H_
#define _SUPER_CUTTER_H_

#include "../../SFramework/SpriteAndAnimation/AnimationSpec.h"
#include "../../SFramework/SpriteAndAnimation/AnimationManager.h"
#include "../../SFramework/GameObject.h"
#include "../../SFramework/Trace.h"
#include "../MegaManUtilities.h"
#include "../../SFramework/Collision.h"
#include "../../SFramework/SFramework.h"

using namespace std;
using namespace s_framework;
#define SUPER_CUTTER_VELOCITY_Y 0.45f

class SuperCutter : public GameObject
{
	AnimationSpec* m_animation = NULL;

public:
	SuperCutter();
	~SuperCutter();
	void render() override;

	void onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector)override;
	void updatePosition()override;
	void calculateCollisionBox()override;
	void setState(int state)override;

	void resetToInit()override;
};

#endif // !_SUPER_CUTTER_H_
