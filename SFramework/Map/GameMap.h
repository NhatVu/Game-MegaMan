#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "../SpriteAndAnimation/Texture.h"
#include "../GameObject.h"
#include "../MapReader/Tmx.h.in"

using namespace Tmx;
using namespace std;
//#include "GameGlobal.h"
namespace s_framework {

class GameMap
{
public:
	GameMap(char* filePath, Texture *ojbectTexture); // texture de goi ham object->setTexture

	Map* GetMap();

	int GetWidth(); // độ rộng của map, đơn vị pixel chứ ko phải số tails như trong tmx file
	int GetHeight();
	int GetTileWidth(); // độ rộng của tileset
	int GetTileHeight();
	vector<Node*> getNodesBackground();
	vector<GameObject*> getListObject(){ return this->mListObjet; };
	
	vector<Node*> getScene();
	~GameMap();

	void LoadMap(char* filePath); // load image(tileset) sử dụng trong map vào biến mListTileset
private:
	vector<Node*> mapNode;
	Map                        *mMap;
	std::map<int, Texture*>          mListTileset;
	std::vector<Node*> mNodesBackground; // danh sách sprite để vẽ background cho map
	std::vector<GameObject*> mListObjet; // danh sách các đối tượng
	Texture* mObjectTexture;
	void parseBackground();
	void parseObjectGroup();
};

}
#endif

