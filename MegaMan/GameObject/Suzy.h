#ifndef _SUZY_H_
#define _SUZY_H_
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


/*
	- Trạng thái Active : mở mắt và di chuyển theo 1 chiều nhất định, x hoặc y
	- Trạng thái Idle: có 2 frame => rồi ngủ trong vòng 3s => chuyển sang trạng thái Active
	- Trạng thái DIE

	Thuộc tính direction trong map: nếu = 1 => di chuyển theo x, -1 di chuyển theo y
*/
#define SUZY_VIRTUAL_WIDTH 16
#define SUZY_VIRTUAL_HEIGHT 16
#define SUZY_VELOCITY 0.15f
class Suzy : public GameObject
{
private:
	AnimationSpec* m_animation = NULL;
	int countFrame;
	int direction;
	int leftToRight;//1: leftToRight, -1 RightToLeft
	int topToBottom; // 1: top to bottom, -1: bottom to top
public:
	Suzy();
	~Suzy();

	void setDirection(int value){
		this->direction = value;
	}

	int getDirection(){
		return this->direction;
	}

	void render() override;

	void onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector)override;
	void updatePosition()override;
	void calculateCollisionBox()override;
	void setState(int state)override;

	void resetToInit()override;
	void die();
};

#endif // !_SUZY_H_
