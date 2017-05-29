#ifndef _BLASTER_H_
#define _BLASTER_H_
#include <d3dx9.h>
#include "../../SFramework/SpriteAndAnimation/AnimationSpec.h"
#include "../../SFramework/SpriteAndAnimation/AnimationManager.h"
#include "../../SFramework/GameObject.h"
#include "../../SFramework/Trace.h"
#include "../MegaManUtilities.h"
#include "../../SFramework/Collision.h"
#include "../../SFramework/Map/ObjectFactory.h"
#include "../../SFramework/Map/ObjectManager.h"

using namespace std;
using namespace s_framework;
/*
	Có 3 trạng thái: Active (open), IDLE(close, ở trạng thái này bắn không chết) và DIE (chết)
	Khi ở open, bắn ra 4 viên đạn với các hướng khác nhau, cố định từ đầu. Mỗi viên cách nhau 20 Frame
	Khi bắn viên cuối cùng => về trạng thái IDLE trong 2s, rồi quay lại trạng thái Active
*/

class Blaster : public GameObject
{
private:
	AnimationSpec* m_animation = NULL;
	int countFrame;
	bool isRender; // lock trong hàm onCollision. mở lock khi render
	void creaetBlasterBullet(float vx, float vy);
public:
	Blaster();
	~Blaster();

	void render() override;
	void onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector)override;
	void updatePosition()override;
	void calculateCollisionBox()override;
	void setState(int state)override;

	void resetToInit()override;
	void die();
};

#endif // !_BLASTER_H_
