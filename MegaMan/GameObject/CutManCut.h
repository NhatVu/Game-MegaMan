#ifndef _CUTMAN_CUT_H_
#define _CUTMAN_CUT_H_
#include <d3dx9.h>
#include "../../SFramework/SpriteAndAnimation/AnimationSpec.h"
#include "../../SFramework/SpriteAndAnimation/AnimationManager.h"
#include "../../SFramework/GameObject.h"
#include "../../SFramework/Trace.h"
#include "../MegaManUtilities.h"
#include "../../SFramework/Collision.h"

using namespace std;
using namespace s_framework;

#define CUTMAN_CUT_VELOCITY_Y 0.45f
#define CUTMAN_CUT_VELOCITY_X 0.07f
#define CUTMAN_CUT_FORCE_ATTACK_DISTANCE 70.0f
#define CUTMAN_CUT_VIRTUAL_WIDTH 10.0f
#define CUTMAN_CUT_VIRTUAL_HEIGHT 10.0f

class CutManCut : public GameObject
{
private:
	AnimationSpec* m_animation = NULL;
	int countFrame;
public:
	CutManCut();
	~CutManCut();

	void render() override;
	void onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector)override;
	void updatePosition()override;
	void calculateCollisionBox()override;
	void setState(int state)override;

	void resetToInit()override;
	void die();
};

#endif // !_CUTMAN_CUT_H_
