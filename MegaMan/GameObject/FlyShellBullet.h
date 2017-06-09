#ifndef _FLY_SHELL_BULLET_H_
#define _FLY_SHELL_BULLET_H_
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
#define FLY_SHELL_BULLET_VELOCITY 0.2f

class FlyShellBullet : public GameObject
{
	AnimationSpec* m_animation = NULL;
	int countFrame;
public:
	FlyShellBullet();
	~FlyShellBullet();

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

#endif // !_FLY_SHELL_BULLET_
