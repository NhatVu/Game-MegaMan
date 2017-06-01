#ifndef _FLY_SHELL_H_
#define _FLY_SHELL_H_
#include <d3dx9.h>
#include "../../SFramework/SpriteAndAnimation/AnimationSpec.h"
#include "../../SFramework/SpriteAndAnimation/AnimationManager.h"
#include "../../SFramework/GameObject.h"
#include "../../SFramework/Trace.h"
#include "../MegaManUtilities.h"
#include "../../SFramework/Collision.h"
#include "../../SFramework/SFramework.h"
#include "FlyShellBullet.h"
using namespace std;
using namespace s_framework;

#define FLY_SHELL_VIRTUAL_WIDTH 15
#define FLY_SHELL_VIRTUAL_HEIGHT 20
#define FLY_SHELL_VELOCITY -0.15f
/*
	di chuyển 1 đoạn A (tương ứng với 2s), từ trạng thái IDLE sang ACTIVE => đứng yên trong 0.5s và bắn đạn => chuyển sang trạng thái IDLE và tiếp tục di chuyển.
*/
class FlyShell : public GameObject
{
private:
	AnimationSpec* m_animation = NULL;
	int countFrame;
	void createBullet(float vx, float vy);
	void createAttack();
	bool isRender;
public:
	FlyShell();
	~FlyShell();

	void render() override;

	void onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector)override;
	void updatePosition()override;
	void calculateCollisionBox()override;
	void setState(int state)override;

	void resetToInit()override;
	void die();
};

#endif // !_FLY_SHELL_H_
