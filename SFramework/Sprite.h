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
	class Sprite : public Node
	{
	private:
		SpriteSpec* m_spriteSpec;
		Texture* m_texture;
		
	public:
		Sprite();
		~Sprite();

		void setTexture(Texture* texture);
		void setSpriteSpec(SpriteSpec* spriteSpec);
		void render()override;
		void update(long delta)override;
		virtual void onKeyUp(int keyCode) = 0;
		virtual void onKeyDown(int keyCode) = 0;
	};

}
#endif // !_CHARACTER_H_


