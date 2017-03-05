#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "Texture.h"
#include "Sprite.h"
#include "MapReader/Tmx.h.in"

//#include "GameGlobal.h"
namespace s_framework {

class GameMap
{
public:
	GameMap(char* filePath);

	Tmx::Map* GetMap();

	int GetWidth(); // độ rộng của map, đơn vị pixel chứ ko phải số tails như trong tmx file
	int GetHeight();
	int GetTileWidth(); // độ rộng của tileset
	int GetTileHeight();

	void Draw(); // vẽ map

	~GameMap();

private:
	void LoadMap(char* filePath); // load image(tileset) sử dụng trong map vào biến mListTileset

	Tmx::Map                        *mMap;
	std::map<int, Texture*>          mListTileset;
};

}
#endif

