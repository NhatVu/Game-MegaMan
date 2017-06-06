#ifndef _BIG_EYE_H_
#define _BIG_EYE_H_
#include "../../SFramework/SpriteAndAnimation/AnimationSpec.h"
#include "../../SFramework/SpriteAndAnimation/AnimationManager.h"
#include "../../SFramework/GameObject.h"
#include "../../SFramework/Trace.h"
#include "../MegaManUtilities.h"
#include "../../SFramework/Collision.h"
#include "../../SFramework/SFramework.h"

using namespace std;
using namespace s_framework;
#define BIG_EYE_VELOCITY_Y 0.45f
#define BIG_EYE_VELOCITY_X 0.07f
#define BIG_EYE_VIRTUAL_WIDTH 30
#define BIG_EYE_VIRTUAL_HEIGHT 40
class BigEye : public GameObject
{
private: 
	AnimationSpec* m_animation = NULL;
	int countFrame;
public:
	BigEye();
	~BigEye();

	void render() override;
	void onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector)override;
	void updatePosition()override;
	void calculateCollisionBox()override;
	void setState(int state)override;

	void resetToInit()override;
	void die();
};

#endif