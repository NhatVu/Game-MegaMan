#include "MegaMan.h"
#include "../../SFramework/SpriteAndAnimation/AnimationManager.h"
#include "../../SFramework/GameTime.h"
#include "../../SFramework/Camera/ViewPort.h"
#include <dinput.h>

using namespace s_framework;
MegaMan::MegaMan() : GameObject()
{
	GameObject::setType(10);
	GameObject::setAcceleration(FPOINT(0, GRAVITATIONAL_ACCELERATION));
	//GameObject::setVelocity(FPOINT(MEGA_MAN_VELOCITY_X, 0.0f));

}


MegaMan::~MegaMan()
{
}

void MegaMan::setTexture(Texture* texture){
	GameObject::setTexture(texture);
}
void MegaMan::render(){
	// nếu như không va chạm với bất kỳ vật nào => đang rơi tự do, chuyển hình thành jump.
	// cá biệt với trường hợp leo thang.
	if (this->getNoCollisionWithAll())
		this->changeAnimation(ECharacter::MEGAMAN, EState::JUMP);
	else m_state->enter(this);
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
}

void MegaMan::processInput(LPDIRECT3DDEVICE9 d3ddv, int Delta){

}

void MegaMan::onKeyDown(int keyCode){
	GameState* state = m_state->onKeyDown(this, keyCode);
	if (state != NULL){
		delete m_state;
		m_state = state;
		m_state->enter(this);
	}
}
void MegaMan::onKeyUp(int KeyCode){
	GameState* state = m_state->onKeyUp(this, KeyCode);
	if (state != NULL){
		delete m_state;
		m_state = state;
		m_state->enter(this);
	}
}

void MegaMan::changeAnimation(int character, int state){
	m_animation = AnimationManager::getInstance()->getAnimationSprites(character, state);
	GameObject::setSpriteSpec(m_animation->getSpriteSpecs()[0]);
}

void MegaMan::processKeyState(BYTE *keyState){
	GameState* state = m_state->processKeyState(this, keyState);
	if (state != NULL){
		delete m_state;
		m_state = state;
		m_state->enter(this);
	}
}

void MegaMan::onCollision(GameObject* staticObject){
	GameState* newState = m_state->onCollision(this, staticObject);
	if (newState != NULL){
		delete m_state;
		m_state = newState;
		m_state->enter(this);
	}
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
	

	// update postion cho viewport. Tại đây, ta chỉ update position theo chiều x mà thôi
	// khi tới một điểm nào đó cố định,ta mới update theo chiều y. như vậy cho dễ.
	FPOINT viewport = ViewPort::getInstance()->getPosition();
	BOX viewportBoundary = ViewPort::getInstance()->getViewportBoundary();
	float tmpX = viewport.x + velocity.x * deltaTime;
	if (this->getPosition().x < SCREEN_WIDTH / 2 + viewportBoundary.x) // không cho di chuyển quá min viewport
		viewport.x = viewportBoundary.x;
	else if (this->getPosition().x > viewportBoundary.x + viewportBoundary.width - SCREEN_WIDTH / 2) // không cho di chuyển quả max viewport
		viewport.x = viewportBoundary.x + viewportBoundary.width - SCREEN_WIDTH;
	else
		viewport.x = tmpX;
	ViewPort::getInstance()->setPosition(viewport);

	// sau khi xét va chạm xong, ta cập nhật lại vận tốc và gia tốc y cho vật. 2 đại lượng này luôn có.
	// kể cả khi vật đứng yên. 
	this->setVelocity(FPOINT(0.0f, velocity.y));
	this->setAcceleration(FPOINT(0.0f, GRAVITATIONAL_ACCELERATION));
}