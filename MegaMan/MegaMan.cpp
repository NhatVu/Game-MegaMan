#include "MegaMan.h"
#include "../SFramework/ResourceManager.h"
#include <dinput.h>

MegaMan::MegaMan():
Sprite()
{
}


MegaMan::~MegaMan()
{
}

void MegaMan::setTexture(Texture* texture){
	Sprite::setTexture(texture);
}
void MegaMan::render(){
	// render current sprite
	Sprite::setSpriteSpec(m_animation->getCurrentSpriteSpec());
	Sprite::render();
}

void MegaMan::processInput(LPDIRECT3DDEVICE9 d3ddv, int Delta){ 
	/*if (isKeyDown(DIK_RIGHT))
	{
		MessageBox(NULL, L"right", NULL, NULL);
	}
	else
	if (isKeyDown(DIK_LEFT))
	{
		MessageBox(NULL, L"left", NULL, NULL);

	}
	else if (isKeyDown(DIK_SPACE))
	{
		MessageBox(NULL, L"Space", NULL, NULL);

	}*/
}

void MegaMan::onKeyDown(int keyCode){
	if (keyCode == DIK_RIGHT)
	{
		trace("right button");
	}
	else
	if (keyCode == DIK_LEFT)
	{
		trace("left button");

	}
	else if (keyCode == DIK_SPACE)
	{
		trace("space button");

	}
}
void MegaMan::onKeyUp(int KeyCode){}

void MegaMan::changeAnimation(int character, int state){
	m_animation = ResourceManager::getInstance()->getAnimationSprites(character, state);
}

void MegaMan::processKeyState(BYTE *keyState){
	if ((keyState[DIK_RIGHT] & 0x80) > 0)
		trace("right button");
	else
	if ((keyState[DIK_LEFT] & 0x80) > 0)
	{
		trace("left button");

	}
	
}

//void MegaMan::updateKeyboard(int keyCode){
//	if (keyCode == DIK_RIGHT)
//	{
//	MessageBox(NULL, L"right", NULL, NULL);
//	}
//	else
//	if (keyCode == DIK_LEFT)
//	{
//	MessageBox(NULL, L"left", NULL, NULL);
//
//	}
//	else if (keyCode == DIK_SPACE)
//	{
//	MessageBox(NULL, L"Space", NULL, NULL);
//
//	}
//}