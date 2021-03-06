#ifndef _MEGAMAN_BULLET_
#define _MEGAMAN_BULLET_
#include <d3dx9.h>
#include "../../SFramework/SpriteAndAnimation/AnimationSpec.h"
#include "../../SFramework/GameObject.h"
#include "../../SFramework/Trace.h"
#include "../MegaManUtilities.h"
#include "../../SFramework/Collision.h"
#include "../../SFramework/SpriteAndAnimation/AnimationManager.h"
#include "../../SFramework/Map/ObjectManager.h"

using namespace std;
using namespace s_framework;

#define MEGAMAN_BULLET_VELOCITY_X 0.45f
#define MEGAMAN_BULLET_VIRTUAL_WIDTH 9.0f
#define MEGAMAN_BULLET_VIRTUAL_HEIGHT 9.0f
class MegaManBullet : public GameObject
{

private:
	AnimationSpec* m_animation = NULL;
	//EState state;
public:
	MegaManBullet();
	~MegaManBullet();

	/*
	Override
	*/
	void render() override;
	void onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector)override;
	void updatePosition()override;
	void calculateCollisionBox()override;
	void setState(int state)override;

	void initFire(); // dua vao vi tri cua megaman -> init state
};


#endif // !_MEGAMAN_BULLET_
