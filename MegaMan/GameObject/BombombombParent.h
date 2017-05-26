#ifndef _BOM_BOM_BOMB_PARENT_H
#define _BOM_BOM_BOMB_PARENT_H
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

#define BOMBOMBOMB_PARENT_VELOCITY_Y 0.5f// 0.7f
#define BOMBOMBOMB_PARENT_EXPLOSIVE_HEIGHT 170 // đến độ cao 190, bom sẽ phát nổ
/*
	Đến 1 độ cao nhất định => bom phát nổ (đồng nghĩ ở trạng thái dead và inactive). Sau 3s (3*FPS frame) => active trở lại
	Việc đếm này ở trong hàm render. 
	Khi phát nổ => tạo ra 1 quả bom con. Nên lưu danh sách 4 quả này kèm vào list để khỏi tốn chi phí tạo lại nhiều lần.

	Enemy này không cần phải xét gia tôc. chỉ cần có vận tốc vy là đủ.
*/
class BombombombParent : public GameObject
{
private:
	AnimationSpec* m_animation = NULL;
	int countFrame;
	bool deactiveInterval;
public:
	BombombombParent();
	~BombombombParent();
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

#endif
