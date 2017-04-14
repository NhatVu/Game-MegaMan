#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Node.h"
#include "SpriteSpec.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "Utilities.h"
#include <list>
#include "Texture.h"

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
		BOX m_collisionBox;
		int type;
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

		void setCollisionBox(BOX box);
		BOX getCollisionBox();

		void setType(int type){ this->type = type; };
		int getType(){ return this->type; };

		void render()override;
		void update(long delta)override;
		virtual void onKeyUp(int keyCode);
		virtual void onKeyDown(int keyCode);
		virtual void processKeyState(BYTE *keyState);


	};

}
#endif // !_CHARACTER_H_


