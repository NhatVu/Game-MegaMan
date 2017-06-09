#ifndef _SUPER_CUTTER_FACTORY_
#define _SUPER_CUTTER_FACTORY_
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

#define SUPPER_CUTTER_FACTORY_ATTACK_DISTANCE 85.0f
#define SUPPER_CUTTER_FACTORY_VIRTUAL_WIDTH 14.0f
#define SUPPER_CUTTER_FACTORY_VIRTUAL_HEIGHT 12.0f
/*
	Nếu mega man tới gần -> tấn công
*/
class SupperCutterFactory : public GameObject
{
private:
	AnimationSpec* m_animation = NULL;
	int countFrame;
	bool isRender;
	bool canAttack;
	void createSuperCutter(float vx, float vy);

public:
	SupperCutterFactory();
	~SupperCutterFactory();

	void render() override;

	void onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector)override;
	void updatePosition()override;
	void calculateCollisionBox()override;
	void setState(int state)override;

	void resetToInit()override;
	//void die();
};

#endif