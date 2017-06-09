#include "MegaMan.h"
#include "../../SFramework/SpriteAndAnimation/AnimationManager.h"
#include "../../SFramework/GameTime.h"
#include "../../SFramework/Camera/ViewPort.h"
#include <dinput.h>
#include "State\MegaManAttackState.h"
#include "../../SFramework/SFramework.h"
#include "State\MegaManBeAttackedState.h"
using namespace s_framework;
MegaMan::MegaMan() : GameObject()
{
	GameObject::setType(ECharacter::MEGAMAN);
	GameObject::setAcceleration(FPOINT(0, GRAVITATIONAL_ACCELERATION));
	//GameObject::setVelocity(FPOINT(MEGA_MAN_VELOCITY_X, 0.0f));
	m_state_attack = new MegaManAttackState();
	canChangeViewportUp = false;
}


MegaMan::~MegaMan()
{
}

void MegaMan::setTexture(LPDIRECT3DTEXTURE9 texture){
	GameObject::setTexture(texture);
}
void MegaMan::render(){
	// nếu như không va chạm với bất kỳ vật nào => đang rơi tự do, chuyển hình thành jump.
	// cá biệt với trường hợp leo thang.
	if (this->getNoCollisionWithAll())
		this->changeAnimation(ECharacter::MEGAMAN, EState::JUMP);
	else m_state->enter(this);

	m_state_attack->enter(this);
	/*if (m_state->name == "Running")
		this->changeAnimation(ECharacter::MEGAMAN, EState::RUNNING);
		*/
	if (this->getStopUpdateAnimation() == 0){

		SpriteSpec* currentSpriteSpec = m_animation->getCurrentSpriteSpec();
		GameObject::setSpriteSpec(currentSpriteSpec);
	}

	// set position to render
	GameObject::render();
	this->setNoCollisionWithAll(true);

	// dành cho lúc bắn viên đạn
	int count = ((MegaManAttackState*)m_state_attack)->countFrame;
	((MegaManAttackState*)m_state_attack)->countFrame++;
	if (((MegaManAttackState*)m_state_attack)->countFrame > FPS / 3){
		((MegaManAttackState*)m_state_attack)->countFrame = 0;
		((MegaManAttackState*)m_state_attack)->isFinishAttack = true;
	}

	// lúc bị tấn công
	if (m_state->name == "BeAttacked"){

		((MegaManBeAttackedState*)m_state)->countFrame++;
		if (((MegaManBeAttackedState*)m_state)->countFrame > 3 * FPS)
		{
			((MegaManBeAttackedState*)m_state)->ChangeToIdleState = true;
		}
		else if (((MegaManBeAttackedState*)m_state)->countFrame > FPS / 2){
			((MegaManBeAttackedState*)m_state)->changeToAttackedFinish = true;
			((MegaManBeAttackedState*)m_state)->countFrame++;
		}
		else
			((MegaManBeAttackedState*)m_state)->countFrame++;
	}
}

void MegaMan::processInput(LPDIRECT3DDEVICE9 d3ddv, int Delta){

}

void MegaMan::onKeyDown(int keyCode){
	if (keyCode == DIK_5){
		ViewPort::getInstance()->setViewportBoundary(BOX(40 * 32, 67 * 32, 24 * 32, 7 * 32));
		ViewPort::getInstance()->setPosition(FPOINT(40 * 32, 67 * 32));
		this->setPostion(FPOINT(41 * 32, 66 * 32));
	}else
	if (keyCode == DIK_6){
		ViewPort::getInstance()->setViewportBoundary(BOX(56 * 32, 59.5f * 32, 8 * 32, 7 * 32));
		ViewPort::getInstance()->setPosition(FPOINT(56 * 32, 59.5f * 32));
		this->setPostion(FPOINT(57 * 32, 65 * 32));

	}else
	if (keyCode == DIK_7){
		ViewPort::getInstance()->setViewportBoundary(BOX(56 * 32, 52 * 32, 8 * 32, 7 * 32));
		ViewPort::getInstance()->setPosition(FPOINT(56 * 32, 52 * 32));
		this->setPostion(FPOINT(57 * 32, 50 * 32));

	}

	GameState* state = m_state->onKeyDown(this, keyCode);
	if (state != NULL){
		delete m_state;
		m_state = state;
		m_state->enter(this);
	}

	state = m_state_attack->onKeyDown(this, keyCode);
	if (state != NULL){
		delete m_state_attack;
		m_state_attack = state;
		m_state_attack->enter(this);
	}
}
void MegaMan::onKeyUp(int KeyCode){
	GameState* state = m_state->onKeyUp(this, KeyCode);
	if (state != NULL){
		delete m_state;
		m_state = state;
		m_state->enter(this);
	}

	state = m_state_attack->onKeyUp(this, KeyCode);
	if (state != NULL){
		delete m_state_attack;
		m_state_attack = state;
		m_state_attack->enter(this);
	}
}

void MegaMan::changeAnimation(int character, int state){
	m_animation = AnimationManager::getInstance()->getAnimationSprites(character, state);
	SpriteSpec* a = m_animation->getSpriteSpecs()[0];
	GameObject::setSpriteSpec(a);
}

void MegaMan::processKeyState(BYTE *keyState){
	GameState* state = m_state->processKeyState(this, keyState);
	if (state != NULL){
		delete m_state;
		m_state = state;
		m_state->enter(this);
	}
}

void MegaMan::onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector){
	GameState* newState = m_state->onCollision(this, staticObject, collisionTime, collisionVector);
	if (newState != NULL){
		delete m_state;
		m_state = newState;
		m_state->enter(this);
	}
}

void MegaMan::calculateCollisionBox(){
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	FPOINT velocity = this->getVelocity();
	velocity.x += this->getAcceleration().x*deltaTime;
	velocity.y += this->getAcceleration().y*deltaTime;

	BOX collisionBox(this->getPosition().x, this->getPosition().y, MEGA_MAN_VIRTUAL_WIDTH,
		MEGA_MAN_VIRTUAL_HEIGHT, velocity.x * deltaTime, velocity.y*deltaTime);
	this->setCollisionBox(collisionBox);
}

// update mega man position and VIEWPORT position 
void MegaMan::updatePosition(){
	FPOINT currentPosition = this->getPosition();
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	FPOINT velocity = this->getVelocity();
	velocity.x += this->getAcceleration().x*deltaTime;
	velocity.y += this->getAcceleration().y*deltaTime;
	currentPosition.x = currentPosition.x + velocity.x*deltaTime;
	currentPosition.y = currentPosition.y + velocity.y*deltaTime;

	this->setPostion(currentPosition);

	// sau khi xét va chạm xong, ta cập nhật lại vận tốc và gia tốc y cho vật. 2 đại lượng này luôn có.
	// kể cả khi vật đứng yên. 
	this->setVelocity(FPOINT(0.0f, velocity.y));
	this->setAcceleration(FPOINT(0.0f, GRAVITATIONAL_ACCELERATION));
}