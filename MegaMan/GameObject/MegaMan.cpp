#include "MegaMan.h"
#include "../../SFramework/ResourceManager.h"
#include "../../SFramework/GameTime.h"
#include <dinput.h>

MegaMan::MegaMan() : GameObject()
{
	GameObject::setVelocity(FPOINT(MEGA_MAN_VELOCITY_X, 0));
}


MegaMan::~MegaMan()
{
}

void MegaMan::setTexture(Texture* texture){
	GameObject::setTexture(texture);
}
void MegaMan::render(){
	// render current sprite
	GameObject::setSpriteSpec(m_animation->getCurrentSpriteSpec());
	GameObject::render();
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
	FPOINT currentPosition = this->getPosition();
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	
	// key right và left thì vy = 0
	if (keyCode == DIK_RIGHT)
	{

		currentPosition.x = currentPosition.x + getVelocity().x*deltaTime;
		this->setPostion(currentPosition);
		trace("deta time " + std::to_string(deltaTime));
		trace("mega man right button onKeyDown\n");
	}
	else
	if (keyCode == DIK_LEFT)
	{
		/*currentPosition.x = currentPosition.x - getVelocity().x*deltaTime;
		this->setPostion(currentPosition);*/
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
	FPOINT currentPosition = this->getPosition();
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	if ((keyState[DIK_RIGHT] & 0x80) > 0)
		trace("mega men right button key state");
	else
	if ((keyState[DIK_LEFT] & 0x80) > 0)
	{
		
			currentPosition.x = currentPosition.x - getVelocity().x*deltaTime;
			this->setPostion(currentPosition);
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