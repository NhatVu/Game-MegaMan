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
	public:
		static   char* SOURCE_TEXTURE_XML;
		static   char* SOURCE_TEXTURE_PNG;
		static   char* SOURCE_MAP_PNG;

	private:
		static TextureManager* mInstance;

		map<int, SpriteSpec*> mTextureMap;

		LPDIRECT3DTEXTURE9 mObjectTexture = NULL;

		LPDIRECT3DTEXTURE9 mMapTexture = NULL;
	public:
		TextureManager();
		~TextureManager();

		static TextureManager* getInstance();

		void setTexture(LPDIRECT3DTEXTURE9 &texture, string src);

		void setObjectTexture();

		void setMapTexture();

		void initSpriteSpecification();

		LPDIRECT3DTEXTURE9 getObjectTexture();

		LPDIRECT3DTEXTURE9 getMapTexture();

		SpriteSpec* getSpriteSpecById(int id);
	};
}

#endif

