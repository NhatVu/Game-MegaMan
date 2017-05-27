#ifndef _MEGAMAN_BE_ATTACKED_STATE_H_
#define _MEGAMAN_BE_ATTACKED_STATE_H_
#include "GameState.h"
#include "../MegaMan.h"
/*
	BeAttacked state có 2 lần chuyển animation. Lần đầu tiên khi vừa bị tấn công -> dùng state Attacked_begin. qua 0.5s -> chuyển sang state Attacked_finish. Ở trạng thái này trong 3s rồi chuyển về idle.
	Trong BeAttacked state xét va chạm với static mà thôi. 
	Ngoài ra, khi bị đụng, mega man lùi về theo hướng bị tấn công 1 khoảng. VD như bị tấn công từ phải sang -> lùi sang trái.
	Lưu ý lúc mega man đang đứng sát viên gạch -> nếu lùi thì sẽ có chuyện gì ???
*/
#define MOVING_X_WHEN_ATTACKED 10
class MegaManBeAttackedState : public GameState
{
public:
	MegaManBeAttackedState();
	~MegaManBeAttackedState();
	GameState* onKeyDown(GameObject* gameObject, int keyCode)override{ return NULL; };
	GameState*  onKeyUp(GameObject* gameObject, int keyCode)override{ return NULL; };
	GameState*  processKeyState(GameObject* gameObject, BYTE *keyState)override{ return NULL; };

	void update(GameObject* gameObject) override;
	void enter(GameObject* gameObject)override;
	GameState* onCollision(GameObject* gameObject, GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector) override;
	bool changeToAttackedFinish;
	bool ChangeToIdleState;
	int countFrame;
};

#endif

