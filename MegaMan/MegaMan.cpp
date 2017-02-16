#include "MegaMan.h"
#include "../SFramework/ResourceManager.h"

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
	if (isKeyDown(DIK_RIGHT))
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

	}
}

void MegaMan::onKeyDown(int KeyCode){}
void MegaMan::onKeyUp(int KeyCode){}

void MegaMan::changeAnimation(int character, int state){
	m_animation = ResourceManager::getInstance()->getAnimationSprites(character, state);
}