#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Node.h"
#include "SpriteAndAnimation/SpriteSpec.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "Utilities.h"
#include <list>
#include "SpriteAndAnimation/Texture.h"
#include "GameTime.h"



using namespace std;
namespace s_framework
{
	// kế thừa m_position, height, width từ Nodes
	// Mỗi đối tượng trong GameObject đề có vận tốc
	class GameObject : public Node
	{
	private:
		SpriteSpec* m_spriteSpec;
		Texture* m_texture;

		FPOINT m_velocity;
		FPOINT m_acceleration;
		BOX m_collisionBox;
		int type;

		int mFlipVertical; // 1 : quay mặt sang phải, -1: quay mặt sang trái
		int canClimb; // 0: không thể, 1: có thể, 2 : có thể leo xuống
	public:
		GameObject();
		~GameObject();

		/*
		* GETTERS AND SETTERS
		*/
		FPOINT getVelocity();
		void setVelocity(FPOINT velocity);

		void setTexture(Texture* texture);
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

		void setAcceleration(FPOINT acceleration){ this->m_acceleration = acceleration; };
		FPOINT getAcceleration(){ return this->m_acceleration; };

		void render()override;
		void update(long delta)override;
		virtual void onKeyUp(int keyCode);
		virtual void onKeyDown(int keyCode);
		virtual void processKeyState(BYTE *keyState);
		virtual void onCollision(GameObject* staticObject);

		virtual void updatePosition();
	};

}
#endif // !_CHARACTER_H_


