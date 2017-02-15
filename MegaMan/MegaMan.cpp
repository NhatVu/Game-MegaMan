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

void MegaMan::processInput(LPDIRECT3DDEVICE9 d3ddv, int Delta){  }

void MegaMan::onKeyDown(int KeyCode){}
void MegaMan::onKeyUp(int KeyCode){}

void MegaMan::changeAnimation(int character, int state){
	m_animation = ResourceManager::getInstance()->getAnimationSprites(character, state);
}