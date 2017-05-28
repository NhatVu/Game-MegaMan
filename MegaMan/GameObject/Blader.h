#ifndef _BLADER_H_
#define _BLADER_H_
#include <d3dx9.h>
#include "../../SFramework/SpriteAndAnimation/AnimationSpec.h"
#include "../../SFramework/SpriteAndAnimation/AnimationManager.h"
#include "../../SFramework/GameObject.h"
#include "../../SFramework/Trace.h"
#include "../MegaManUtilities.h"
#include "../../SFramework/Collision.h"

using namespace std;
using namespace s_framework;

//#define BLADER_VELOCITY_Y 0.45f
#define BLADER_VELOCITY_X 0.07f
#define BLADER_ACTIVE_DISTANCE 100.0f
#define BLADER_FORCE_ATTACK_DISTANCE 70.0f
#define BLADER_VIRTUAL_WIDTH 14.0f
#define BLADER_VIRTUAL_HEIGHT 12.0f
#define FRAME_ATTACK 20

/*
	-Nếu khoảng cách từ megaman và blader > 1 khoảng A, blader chỉ có vận tốc vx, không có vy và ay. vx = BLADER_VELOCITY_X
	-Nếu khoảng cách từ megaman và blader < 1 khoảng A => Blader di chuyển theo hình chữ V, ta phải lưu vị trí iniPposition và attackPosition (vị trí này là vị trí megaman tại thời điểm tấn công). Blader di chuyển tới điểm attackPos trong 1s.
	Sau đó, vy đảo chiều, di chuyển đến vị trí y = initPos.y
	Sử dụng biến attackCountFrame để quản lý việc này.

*/
class Blader : public GameObject
{
private:
	int attackCountFrame;
	AnimationSpec* m_animation = NULL;
	bool isAttacked;
	FPOINT attackPos;
public:
	Blader();
	~Blader();

	void render() override;
	void onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector)override;
	void updatePosition()override;
	void calculateCollisionBox()override;
	void setState(int state)override;

	void resetToInit()override;
	void die();
};

#endif // !_BLADER_H_
