#ifndef _KAMADOMA_H_
#define _KAMADOMA_H_
#include <d3dx9.h>
#include "../../SFramework/SpriteAndAnimation/AnimationSpec.h"
#include "../../SFramework/SpriteAndAnimation/AnimationManager.h"
#include "../../SFramework/GameObject.h"
#include "../../SFramework/Trace.h"
#include "../MegaManUtilities.h"
#include "../../SFramework/Collision.h"

using namespace std;
using namespace s_framework;

#define KAMADOMA_VELOCITY_Y 0.55f
#define KAMADOMA_VELOCITY_X 0.07f
#define KAMADOMA_ACTIVE_DISTANCE 100.0f
#define KAMADOMA_FORCE_ATTACK_DISTANCE 70.0f
#define KAMADOMA_VIRTUAL_WIDTH 14.0f
#define KAMADOMA_VIRTUAL_HEIGHT 12.0f
/*
	Nếu khoảng cách từ kamadoma và megaman < 1 số A =>  kamadoma di chuyển bình thường với vx normal
	Nếu khoảng cách > A => kamadoma vx = A/dt để nó di chuyển chạm vào vị trí trước đó của mega man. 

	Khi megaman va chạm với kamadoma thì bị lùi lại 1 ít và flip theo trục y. (đang quay mặt phải => va chạm => quay mặt trái)
*/
class Kamadoma : public GameObject
{
private:
	AnimationSpec* m_animation = NULL;
	EState state;
	bool canAttack;
	bool isLeftCollision = false; // va cham trai voi static
	bool isRightCollision = false;// va cham phai voi static
public:
	Kamadoma();
	~Kamadoma();
	/*
	Override
	*/
	void render() override;
	void onKeyDown(int keyCode) override;
	void onKeyUp(int keyCode) override;

	//void updateKeyboard(int keyCode)override;
	void processKeyState(BYTE *keyState)override;
	void onCollision(GameObject* staticObject)override;
	void updatePosition()override;
	void setState(EState state){
		this->state = state;
		m_animation = AnimationManager::getInstance()->getAnimationSprites(ECharacter::KAMADOMA, state);
		GameObject::setSpriteSpec(m_animation->getSpriteSpecs()[0]);
	}

	void resetToInit()override;
};

#endif // !_KAMADOMA_H_
