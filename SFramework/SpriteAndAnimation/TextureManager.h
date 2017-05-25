#ifndef _TEXTURE_MANAGER_H
#define _TEXTURE_MANAGER_H

#include <d3dx9.h>
#include "SpriteSpec.h"
#include <map>
#include <string>

using namespace std;
namespace s_framework {
	class TextureManager
	{
	private:
		static constexpr const char* SOURCE_TEXTURE_XML = "Resources/texture.xml";
		static constexpr const char* SOURCE_TEXTURE_PNG = "Resources/texture.png";
		static constexpr const char* SOURCE_MAP_PNG = "Resources/Bombman's Stage - Mephea.png";

		static TextureManager* mInstance;

		map<int, SpriteSpec*> mTextureMap;

		LPDIRECT3DTEXTURE9 mObjectTexture = NULL;

		LPDIRECT3DTEXTURE9 mMapTexture = NULL;
	public:
		TextureManager();
		~TextureManager();

		static TextureManager* getInstance();

		void setTextureMap();

		void setTexture(LPDIRECT3DTEXTURE9 texture, string src);

		void setObjectTexture();

		void setMapTexture();

		LPDIRECT3DTEXTURE9 getObjectTexture();

		LPDIRECT3DTEXTURE9 getMapTexture();

		SpriteSpec* getSpriteSpecById(int id);
	};
}

#endif

