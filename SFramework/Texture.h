#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include<d3dx9.h>
#include "SpriteSpec.h"
#include <map>
#include <string>

using namespace std;

namespace s_framework{


	class Texture
	{
	
	private:
		static Texture* m_instance;
		LPDIRECT3DTEXTURE9 m_texture = NULL;		// The “container”
		//LPD3DXSPRITE _SpriteHandler;

		map<int, SpriteSpec*> m_mapTexture;
		//SpriteSpec t_spriteSpec;

	private:
		void loadImageToTexture(string imageSource);
		void parseTextureXMLFile(string xmlFile);

	public:
		static Texture* getInstance();
		void init(string imageSource, string textureXML);
		LPDIRECT3DTEXTURE9 getTexture();
		SpriteSpec* getSpriteSpecById(int id);

		// Render current sprite at location (X,Y) at the target surface
		//void Render(int X, int Y);
		Texture();
		~Texture();
	};
}
#endif // !_TEXTURE_H_



