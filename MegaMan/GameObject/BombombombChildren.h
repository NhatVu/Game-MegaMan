#ifndef _BOMBOMBOMB_CHILDREN_H
#define _BOMBOMBOMB_CHILDREN_H_
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

#define BOMBOMBOMB_CHILDREN_VELOCITY_X_STANDARD 0.1f
#define BOMBOMBOMB_CHILDREN_VELOCITY_Y 0.1f
class BombombombChildren : public GameObject
{
	AnimationSpec* m_animation = NULL;
	int countFrame;
	bool deactiveInterval;
public:
	BombombombChildren();
	~BombombombChildren();
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

#endif // !_BOMBOMBOMB_CHILDREN_H
