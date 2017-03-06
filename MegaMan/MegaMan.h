#ifndef _MEGA_MAN_H_
#define _MEGA_MAN_H_

#include <d3dx9.h>
#include "../SFramework/AnimationSpec.h"
#include "../SFramework/Sprite.h"
#include "../SFramework/Trace.h"
#include <vector>

using namespace s_framework;
class MegaMan : public Sprite
{
public:
	MegaMan();
	~MegaMan();

private: 
	AnimationSpec* m_animation = NULL;

public:
	void setTexture(Texture* texture);
	void render() override;
	virtual void processInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);

	void onKeyDown(int keyCode) override;
	void onKeyUp(int keyCode) override;

	//void updateKeyboard(int keyCode)override;
	void changeAnimation(int character, int state);
	void processKeyState(BYTE *keyState)override;
};

#endif // !_MEGA_MAN_H_



