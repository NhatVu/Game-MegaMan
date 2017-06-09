#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Node.h"
#include "SpriteAndAnimation/SpriteSpec.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "Utilities.h"
#include <list>
#include "GameTime.h"
#include "../MegaMan/MegaManUtilities.h"


using namespace std;
namespace s_framework
{
	// kế thừa m_position, height, width từ Nodes
	// Mỗi đối tượng trong GameObject đề có vận tốc
	class GameObject : public Node
	{
	private:
		SpriteSpec* m_spriteSpec;
		LPDIRECT3DTEXTURE9 mTexture;
		FPOINT m_velocity;
		FPOINT m_acceleration;
		BOX m_collisionBox;
		int type;

		int mFlipVertical; // 1 : quay mặt sang phải, -1: quay mặt sang trái
		int canClimb; // 0: không thể, 1: có thể, 2 : có thể leo xuống
		int noCollisionWithAll;
		int stopUpdateAnimation; // ngừng update animation khi object idle
		float timeCollision;
		int objectID;

		FPOINT initPosition;
		int state;
		bool isInactive;// kh ở trạng thái chết -> true. khi ra khỏi viewport => false. và khi true, không xét va chạm, không vẽ
		int blood;
		int attackDamage;
		int point;
	public:
		GameObject();
		~GameObject();

		void setTexture(LPDIRECT3DTEXTURE9 texture);

		/*
		* GETTERS AND SETTERS
		*/
		FPOINT getVelocity();
		void setVelocity(FPOINT velocity);

		void setSpriteSpec(SpriteSpec* spriteSpec);
		SpriteSpec* getSpriteSpec(){ return this->m_spriteSpec; };

		void setCollisionBox(BOX box);
		BOX getCollisionBox();

		void setType(int type){ this->type = type; };
		int getType(){ return this->type; };

		void setFlipVertical(int flipVertical){
			if (mFlipVertical != flipVertical)
				this->mFlipVertical = flipVertical;
		}

		int getFlipVertical(){
			return this->mFlipVertical;
		}

		void setCanClimb(int value){
			this->canClimb = value;
		}

		int getCanClimb(){
			return this->canClimb;
		}

		void setNoCollisionWithAll(int value){
			this->noCollisionWithAll = value;
		}

		int getNoCollisionWithAll(){
			return this->noCollisionWithAll;
		}

		void setStopUpdateAnimation(int value){
			this->stopUpdateAnimation = value;
		}

		int getStopUpdateAnimation(){
			return this->stopUpdateAnimation;
		}

		void setAcceleration(FPOINT acceleration){ this->m_acceleration = acceleration; };
		FPOINT getAcceleration(){ return this->m_acceleration; };

		float getTimeCollision(){ return this->timeCollision; }
		void setTimeCollision(float time){ this->timeCollision = time; }

		int getObjectID(){ return this->objectID; }
		void setObjectID(int id){
			if (objectID == -1)
				objectID = id;
		}

		FPOINT getInitPosition(){
			return this->initPosition;
		}
		void setInitPosition(FPOINT initPosition){
			this->initPosition = initPosition;
		}
		
		void virtual setState(int state){
			this->state = state;
		};
		int getState(){
			return this->state;
		}

		void setIsInactive(bool value){
			this->isInactive = value;
		}

		bool getIsInactive(){
			return this->isInactive;
		}

		void setBlood(int value){
			this->blood = value;
		}

		int getBlood(){ return this->blood; }
		void setAttackDamage(int value){
			this->attackDamage = value;
		}
		int getAttackDamage(){
			return this->attackDamage;
		}

		void setPoint(int value){
			this->point = value;
		}
		int getPoint(){
			return this->point;
		}
		void render()override;
		void update(long delta)override;
		virtual void onKeyUp(int keyCode);
		virtual void onKeyDown(int keyCode);
		virtual void processKeyState(BYTE *keyState);
		virtual void onCollision(GameObject* staticObject, float collisionTime, D3DXVECTOR2 collisionVector);
		virtual void calculateCollisionBox(){};
		virtual void updatePosition();
		virtual void resetToInit(){}
	};

}
#endif // !_CHARACTER_H_


