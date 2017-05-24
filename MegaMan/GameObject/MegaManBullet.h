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

#define MEGAMAN_BULLET_VELOCITY_X 0.2f
#define MEGAMAN_BULLET_VIRTUAL_WIDTH 9.0f
#define MEGAMAN_BULLET_VIRTUAL_HEIGHT 9.0f
class MegaManBullet : public GameObject
{

private:
	AnimationSpec* m_animation = NULL;
	EState state;
public:
	MegaManBullet();
	~MegaManBullet();

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
		m_animation = AnimationManager::getInstance()->getAnimationSprites(ECharacter::MEGAMAN_BULLET, state);
		GameObject::setSpriteSpec(m_animation->getSpriteSpecs()[0]);
	}

	void initFire(); // dua vao vi tri cua megaman -> init state
};


#endif // !_MEGAMAN_BULLET_
