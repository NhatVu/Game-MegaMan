#include "CutMan.h"
#include "../GameObject/MegaMan.h"
#include <cmath>
#include "../../SFramework/SFramework.h"
CutMan::CutMan()
{
	this->colliseLeftRight = false;
	this->isRender = false;
	this->canChangeState = false;
	this->jumpingCollideBottom = true;
	this->countFrameIdle = 0;

	 //create cutman Cut
	this->cutManCut = (CutManCut*)ObjectFactory::createObject(ECharacter::CUTMAN_CUT);
	this->cutManCut->setObjectID(ObjectManager::notInMapObjectId++);
	ObjectManager::getInstance()->addObjectToActiveObject(this->cutManCut);
}


CutMan::~CutMan()
{
}

void CutMan::updatePosition(){
	if (this->getIsInactive())
		return;
	FPOINT currentPosition = this->getPosition();
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	FPOINT velocity = this->getVelocity();
	velocity.x += this->getAcceleration().x*deltaTime;
	velocity.y += this->getAcceleration().y*deltaTime;
	currentPosition.x = currentPosition.x + velocity.x*deltaTime;
	currentPosition.y = currentPosition.y + velocity.y*deltaTime;

	//velocity.x = CUTMAN_VELOCITY_X;
	this->setPostion(currentPosition);
	this->setVelocity(velocity);
	this->setAcceleration(FPOINT(0.0f, GRAVITATIONAL_ACCELERATION / 2));
	returnCutIdle();
	cutManCut->updatePosition();
}

void CutMan::onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector){
	SpriteSpec* currentSpriteSpec = this->getSpriteSpec();
	D3DXVECTOR2 normal = collisionVector;
	int staticObjectType = staticObject->getType();
	FPOINT megaManPos = ObjectManager::getInstance()->getMegaMan()->getPosition();

	if (megaManPos.x - this->getPosition().x >10){
		if(this->getState() != EState::IDLE)
		this->setVelocity(FPOINT(CUTMAN_VELOCITY_X, this->getVelocity().y));
		this->setFlipVertical(-1);
	}
	else if ( megaManPos.x - this->getPosition().x < -10)
	{
		if (this->getState() != EState::IDLE)
		this->setVelocity(FPOINT(-CUTMAN_VELOCITY_X, this->getVelocity().y));
		this->setFlipVertical(1);
	}

	if (this->isRender){
		this->isRender = false;
		this->canChangeState = false;
		if (abs(megaManPos.x - this->getPosition().x) < CUTMAN_JUMPING_DISTANCE){
			if (this->getState() == EState::RUNNING){
				changeToJump();
			}
		}
		else if (this->getState() == EState::IDLE && this->countFrameIdle >= 1.0f*FPS){
			this->countFrameIdle = 0;
			changeToRun();
		}

		
	}

	if (collisionTime > 0.0f && collisionTime < 1.0f){
		//this->setNoCollisionWithAll(false);
		//((MegaMan*)this)->changeAnimation(ECharacter::MEGAMAN, EState::IDLE);
		//// cho những vật chỉ cần va chạm, không cần hướng 
		//if (staticObjectType == ECharacter::BLADER || staticObjectType == ECharacter::KAMADOMA
		//	|| staticObjectType == ECharacter::BLASTER_BULLET || staticObjectType == ECharacter::BLASTER
		//	|| staticObjectType == ECharacter::SUZY || staticObjectType == ECharacter::SCREW_BULLET || staticObjectType == ECharacter::SUPER_CUTTER || staticObjectType == ECharacter::BIG_EYE){
		//	FPOINT newPosition = this->getPosition();

		//	if (newPosition.x > staticObject->getPosition().x)
		//		newPosition.x += MOVING_X_WHEN_ATTACKED;
		//	else newPosition.x -= MOVING_X_WHEN_ATTACKED;
		//	this->setPostion(newPosition);
		//	return new MegaManBeAttackedState();
		//}

		if (this->getState() == EState::IDLE){
			 onCollisionIdleState(staticObject, collisionTime, collisionVector);
		}
		else if (this->getState() == EState::RUNNING){
			 onCollisionRunningState(staticObject, collisionTime, collisionVector);
		}
		else if (this->getState() == EState::JUMP){
			 onCollisionJumpingState(staticObject, collisionTime, collisionVector);
		}
		else if (this->getState() == EState::ATTACKED_BEGIN){
			 onCollisionBeAttackedState(staticObject, collisionTime, collisionVector);
		}
		
	}
}

void CutMan::resetToInit(){
	GameObject::setAcceleration(FPOINT(0, GRAVITATIONAL_ACCELERATION / 2));

	this->setPostion(this->getInitPosition());
	BOX oldCollisionBox = this->getCollisionBox();
	oldCollisionBox.x = this->getPosition().x;
	oldCollisionBox.y = this->getPosition().y;
	oldCollisionBox.width = CUTMAN_VIRTUAL_WIDTH;
	oldCollisionBox.height = CUTMAN_VIRTUAL_HEIGHT;
	oldCollisionBox.vx = 0.0f;
	oldCollisionBox.vy = 0.0f;
	this->setCollisionBox(oldCollisionBox);

	this->setState(EState::IDLE);
	this->setAttackDamage(2);
	this->setBlood(1);

	cutManCut->resetToInit();
}

void CutMan::setState(int state){
	//this->state = state;
	GameObject::setState(state);
	m_animation = AnimationManager::getInstance()->getAnimationSprites(ECharacter::CUTMAN, state);
	GameObject::setSpriteSpec(m_animation->getSpriteSpecs()[0]);
}
void CutMan::render() {
	this->colliseLeftRight = false;
	this->isRender = true;
	if (this->getState() == EState::IDLE)
		this->countFrameIdle++;
	SpriteSpec* currentSpriteSpec = m_animation->getCurrentSpriteSpec();
	GameObject::setSpriteSpec(currentSpriteSpec);
	// set position to render
	GameObject::render();

	cutManCut->render();
}

void CutMan::calculateCollisionBox(){
	if (this->getIsInactive())
		return;
	DWORD deltaTime = GameTime::getInstance()->getDeltaTime();
	FPOINT velocity = this->getVelocity();

	velocity.x += this->getAcceleration().x*deltaTime;
	velocity.y += this->getAcceleration().y*deltaTime;

	// set Collision BOX for CUTMAN. 
	BOX collisionBox(this->getPosition().x, this->getPosition().y, CUTMAN_VIRTUAL_WIDTH,
		CUTMAN_VIRTUAL_HEIGHT, velocity.x * deltaTime, velocity.y*deltaTime);
	this->setCollisionBox(collisionBox);
}

void CutMan::onCollisionIdleState(GameObject* staticObject, float collisionTime, D3DXVECTOR2 normal){
	/*
	NOTE : Khi xét va chạm, không set vị trí và chạm giữa 2 vật trùng nhau mà phải cho chúng nó lệch nhau ít nhất 1px.
	- Position ở đây là top-left của vật.
	*/
	//vật đi từ trên xuống
	if (normal.x == 0.0f && normal.y == 1.0f)
	{
		FPOINT newPosition = this->getPosition();
		switch (staticObject->getType()){
			// với static object 
		case ECharacter::STATIC:
			newPosition.y = CUTMAN_VIRTUAL_HEIGHT + staticObject->getCollisionBox().y + 1;
			this->setPostion(newPosition);
			this->colliseLeftRight = true;
			/*
			Khi mega man đứng trên mặt đất, có phản lực N triệt tiêu lực hấp dẫn. Do đó có thể coi
			gia tốc trọng từng = 0 và v.y = 0;
			*/
			this->setAcceleration(FPOINT(0.0f, 0.0f));
			this->setVelocity(FPOINT(this->getVelocity().x, 0.0f));
			break;
		default:
			break;
		}
	}
	// vật đi chuyển từ dưới lên
	else if (normal.x == 0.0f && normal.y == -1.0f)
	{
	}
	// vật đi từ phải sang
	else if (normal.x == 1.0f && normal.y == 0.0f){
		FPOINT newPosition = this->getPosition();
		switch (staticObject->getType()){
		case ECharacter::STATIC:
			newPosition.x = staticObject->getCollisionBox().x + staticObject->getCollisionBox().width + 1;
			this->setPostion(newPosition);
			this->colliseLeftRight = true;

			this->setVelocity(FPOINT(0.0f, this->getVelocity().y));
			break;
		default:
			break;
		}
	}
	else
		// vật đi từ trái sang
	if (normal.x == -1.0f && normal.y == 0.0f){
		FPOINT newPosition = this->getPosition();
		switch (staticObject->getType()){
		case ECharacter::STATIC:
			newPosition.x = staticObject->getCollisionBox().x - MEGA_MAN_VIRTUAL_WIDTH - 1;
			this->setPostion(newPosition);
			this->setVelocity(FPOINT(0.0f, this->getVelocity().y));
			break;
		default:
			break;
		}
	}
}

void CutMan::onCollisionRunningState(GameObject* staticObject, float collisionTime, D3DXVECTOR2 normal){
	//vật đi từ trên xuống
	if (normal.x == 0.0f && normal.y == 1.0f)
	{
		FPOINT newPosition = this->getPosition();
		switch (staticObject->getType()){
			// với static object 
		case ECharacter::STATIC:
			newPosition.y = CUTMAN_VIRTUAL_HEIGHT + staticObject->getCollisionBox().y + 1;
			this->setPostion(newPosition);
			/*
			Khi mega man đứng trên mặt đất, có phản lực N triệt tiêu lực hấp dẫn. Do đó có thể coi
			gia tốc trọng từng = 0 và v.y = 0;
			*/
			this->setAcceleration(FPOINT(0.0f, 0.0f));
			this->setVelocity(FPOINT(this->getVelocity().x, 0.0f));
			break;
		default:
			break;
		}
	}
	// vật đi chuyển từ dưới lên
	else if (normal.x == 0.0f && normal.y == -1.0f)
	{
	}
	// vật đi từ phải sang
	else if (normal.x == 1.0f && normal.y == 0.0f){
		FPOINT newPosition = this->getPosition();
		switch (staticObject->getType()){
		case ECharacter::STATIC:
			newPosition.x = staticObject->getCollisionBox().x + staticObject->getCollisionBox().width + 1;
			this->setPostion(newPosition);
			this->colliseLeftRight = true;

			this->setVelocity(FPOINT(0.0f, this->getVelocity().y));
			break;
		default:
			break;
		}
	}
	else
		// vật đi từ trái sang
	if (normal.x == -1.0f && normal.y == 0.0f){
		FPOINT newPosition = this->getPosition();
		switch (staticObject->getType()){
		case ECharacter::STATIC:
			newPosition.x = staticObject->getCollisionBox().x - MEGA_MAN_VIRTUAL_WIDTH - 1;
			this->setPostion(newPosition);
			this->colliseLeftRight = true;
			this->setVelocity(FPOINT(0.0f, this->getVelocity().y));
			break;
		default:
			break;
		}
	}
}


void CutMan::onCollisionAttackState(GameObject* staticObject, float collisionTime, D3DXVECTOR2 normal){}

void CutMan::onCollisionBeAttackedState(GameObject* staticObject, float collisionTime, D3DXVECTOR2 normal){}


void CutMan::onCollisionJumpingState(GameObject* staticObject, float collisionTime, D3DXVECTOR2 normal){
	FPOINT megaManPos = ObjectManager::getInstance()->getMegaMan()->getPosition();

	if (normal.x == 0.0f && normal.y == 1.0f)
	{
		FPOINT newPosition = this->getPosition();
		switch (staticObject->getType()){
			// với static object 
		case ECharacter::STATIC:
			newPosition.y = CUTMAN_VIRTUAL_HEIGHT + staticObject->getCollisionBox().y + 1;
			this->setPostion(newPosition);
			/*
			Khi mega man đứng trên mặt đất, có phản lực N triệt tiêu lực hấp dẫn. Do đó có thể coi
			gia tốc trọng từng = 0 và v.y = 0;
			*/
			this->setAcceleration(FPOINT(0.0f, 0.0f));
			this->jumpingCollideBottom = true;
			this->setVelocity(FPOINT(this->getVelocity().x, CUTMAN_VELOCITY_Y));
			if (abs(megaManPos.x - this->getPosition().x) > CUTMAN_JUMPING_DISTANCE){
				changeToIdle();
			}
			break;
		default:
			break;
		}
	}
	// vật đi chuyển từ dưới lên
	else if (normal.x == 0.0f && normal.y == -1.0f)
	{
		FPOINT newPosition = this->getPosition();
		switch (staticObject->getType()){
		case ECharacter::STATIC:
			newPosition.y = staticObject->getCollisionBox().y - staticObject->getCollisionBox().height - 1;
			this->setPostion(newPosition);
			//Lẽ ra phải là this->getVelocity().y nhưng vì để như vậy, vận tốc quá lớn dẫn đến frame tiếp theo,
			// vật đã bị trùng vào nền => ko xảy ra va chạm theo swapaabb. nên ta bị dội ngược lại cho va chạm với bottom viên gạch, vận tốc lúc này chỉ có gia tốc y sinh ra, không do -vy còn dư thừa.

			this->setVelocity(FPOINT(this->getVelocity().x, 0.0f));
			break;
		default:
			break;
		}
	}
	// vật đi từ phải sang
	else if (normal.x == 1.0f && normal.y == 0.0f){
		FPOINT newPosition = this->getPosition();
		switch (staticObject->getType()){
		case ECharacter::STATIC:
			newPosition.x = staticObject->getCollisionBox().x + staticObject->getCollisionBox().width + 1;
			this->setPostion(newPosition);
			this->colliseLeftRight = true;

			this->setVelocity(FPOINT(0.0f, this->getVelocity().y));
			break;
		default:
			break;
		}
	}
	else
		// vật đi từ trái sang
	if (normal.x == -1.0f && normal.y == 0.0f){
		FPOINT newPosition = this->getPosition();
		switch (staticObject->getType()){
		case ECharacter::STATIC:
			newPosition.x = staticObject->getCollisionBox().x - MEGA_MAN_VIRTUAL_WIDTH - 1;
			this->setPostion(newPosition);			
			this->colliseLeftRight = true;

			this->setVelocity(FPOINT(0.0f, this->getVelocity().y));
			break;
		default:
			break;
		}
	}
}


void CutMan::changeToIdle(){
	this->setState(EState::IDLE);
	//this->setAcceleration(FPOINT(0.0f, 0.0f));
	this->setVelocity(FPOINT(0.0f, 0.0f));
}
void CutMan::changeToRun(){
	this->setState(EState::RUNNING);
	this->setVelocity(FPOINT(CUTMAN_VELOCITY_X, 0.0f));
	//this->setAcceleration(FPOINT())
}

void CutMan::changeToJump(){
	this->setState(EState::JUMP);
	this->setVelocity(FPOINT(CUTMAN_VELOCITY_X, CUTMAN_VELOCITY_Y));
	this->setAcceleration(FPOINT(0.0f, GRAVITATIONAL_ACCELERATION / 2));

}

void CutMan::createAttack(){

}
void CutMan::returnCutIdle(){
	cutManCut->setVelocity(FPOINT(0.0f, 0.0f));
	int tempX = 0;
	if (this->getFlipVertical() == 1) // quay mặt sang trái
	{
		tempX = this->getPosition().x - 2;
		tempX = tempX + (this->getSpriteSpec()->getWidth()  - cutManCut->getSpriteSpec()->getWidth()) / 2;
		if (this->getState() == EState::IDLE)
			tempX += 6;
	}
	else{
		tempX = this->getPosition().x + 5;
		tempX = tempX + (this->getSpriteSpec()->getWidth() - cutManCut->getSpriteSpec()->getWidth()) / 2;
		if (this->getState() == EState::IDLE)
			tempX -= 8;
	}
	cutManCut->setPostion(FPOINT(tempX, this->getPosition().y + cutManCut->getSpriteSpec()->getHeight()));
	cutManCut->calculateCollisionBox();
}
