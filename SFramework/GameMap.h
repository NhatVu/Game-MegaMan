#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "Texture.h"
#include "GameObject.h"
#include "MapReader/Tmx.h.in"

using namespace Tmx;
//#include "GameGlobal.h"
namespace s_framework {

class GameMap
{
public:
	GameMap();
	GameMap(char* filePath);

	Map* GetMap();

	int GetWidth(); // độ rộng của map, đơn vị pixel chứ ko phải số tails như trong tmx file
	int GetHeight();
	int GetTileWidth(); // độ rộng của tileset
	int GetTileHeight();

	void Draw(); // vẽ map
	vector<Node*> getScene();

	~GameMap();

	void LoadMap(char* filePath); // load image(tileset) sử dụng trong map vào biến mListTileset
private:
	vector<Node*> mapNode;
	Map                        *mMap;
	std::map<int, Texture*>          mListTileset;
};

}
#endif

