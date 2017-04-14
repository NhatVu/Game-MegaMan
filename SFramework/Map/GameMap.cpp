#include "GameMap.h"
#include "../SpriteAndAnimation/SpriteSpec.h"
using namespace s_framework;

GameMap::GameMap(char* filePath, Texture* objectTexture)
{
	this->mObjectTexture = objectTexture;
	LoadMap(filePath);
	parseBackground();
	parseObjectGroup();
}

GameMap::~GameMap()
{
	for (auto const &ent1 : mListTileset){
		delete ent1.second;
	}

	for (int i = 0; i < mapNode.size(); i++){
		delete mapNode[i];
	}

	for (int i = 0; i < mNodesBackground.size(); i++)
		delete mNodesBackground[i];


	mapNode.clear();
	mNodesBackground.clear();
	delete mMap;
}

vector<Node*> GameMap::getNodesBackground(){
	return mNodesBackground;
}

void GameMap::LoadMap(char* filePath)
{
	mMap = new Tmx::Map();
	mMap->ParseFile(filePath);

	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = this->GetWidth() - 1;
	r.bottom = this->GetHeight() - 1;

	for (size_t i = 0; i < mMap->GetNumTilesets(); i++)
	{
		const Tileset *tileset = mMap->GetTileset(i);

		Texture *texture = new Texture();
		texture->init("Resources\\" + tileset->GetImage()->GetSource());

		// load texutre use in map into mListTileset
		mListTileset[i] = texture;
	}
}

Tmx::Map* GameMap::GetMap()
{
	return mMap;
}

int GameMap::GetWidth()
{
	return mMap->GetWidth() * mMap->GetTileWidth();
}

int GameMap::GetHeight()
{
	return mMap->GetHeight() * mMap->GetTileHeight();
}

int GameMap::GetTileWidth()
{
	return mMap->GetTileWidth();
}

int GameMap::GetTileHeight()
{
	return mMap->GetTileHeight();
}

void GameMap::parseBackground()
{
	for (size_t i = 0; i < mMap->GetNumTileLayers(); i++)
	{
		const Tmx::TileLayer *layer = mMap->GetTileLayer(i);

		if (!layer->IsVisible())
		{
			continue;
		}

		RECT sourceRECT;

		int tileWidth = mMap->GetTileWidth();
		int tileHeight = mMap->GetTileHeight();
		int mapHeight = mMap->GetHeight() * tileHeight;


		for (size_t m = 0; m < layer->GetHeight(); m++)
		{
			for (size_t n = 0; n < layer->GetWidth(); n++)
			{
				int tilesetIndex = layer->GetTileTilesetIndex(n, m);

				if (tilesetIndex != -1)
				{
					const Tmx::Tileset *tileSet = mMap->GetTileset(tilesetIndex);

					int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
					int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;

					Texture* texture = mListTileset[layer->GetTileTilesetIndex(n, m)];

					//tile index
					int tileID = layer->GetTileId(n, m);

					int y = tileID / tileSetWidth; // chỉ số của tileId trong tileset
					int x = tileID % tileSetWidth;

					sourceRECT.top = y * tileHeight;
					sourceRECT.bottom = sourceRECT.top + tileHeight;
					sourceRECT.left = x * tileWidth;
					sourceRECT.right = sourceRECT.left + tileWidth;

					//tru tilewidth/2 va tileheight/2 vi GameObject ve o vi tri giua hinh anh cho nen doi hinh de cho
					//dung toa do (0,0) cua the gioi thuc la (0,0) neu khong thi se la (-tilewidth/2, -tileheigth/2);
					FPOINT position(n * tileWidth + tileWidth / 2, m * tileHeight + tileHeight / 2);
					position.y = mapHeight - position.y;
					/*
					Code demo xét theo hệ trục của màn hình với y hướng xuống. nên phải thiết lập lại độ cao cho tile trong map.
					*/
					SpriteSpec* spriteSpec = new SpriteSpec();
					spriteSpec->setWidth(tileWidth);
					spriteSpec->setHeight(tileHeight);
					spriteSpec->setX(sourceRECT.left);
					spriteSpec->setY(sourceRECT.top);
					
					GameObject* sprite = new GameObject();
					sprite->setTexture(texture);
					sprite->setSpriteSpec(spriteSpec);
					sprite->setPostion(position);
					//sprite->render();
					mNodesBackground.push_back(sprite);
					//sprite->Draw(position, sourceRECT, D3DXVECTOR2());
				}
			}
		}
	}
}

vector<Node*> GameMap::getScene(){

	for (size_t i = 0; i < mMap->GetNumTileLayers(); i++)
	{
		const Tmx::TileLayer *layer = mMap->GetTileLayer(i);

		if (!layer->IsVisible())
		{
			continue;
		}

		RECT sourceRECT;

		int tileWidth = mMap->GetTileWidth();
		int tileHeight = mMap->GetTileHeight();
		int mapWidth = mMap->GetWidth() * tileWidth;
		int mapHeight = mMap->GetHeight() * tileHeight;

		for (size_t m = 0; m < layer->GetHeight(); m++)
		{
			for (size_t n = 0; n < layer->GetWidth(); n++)
			{
				int tilesetIndex = layer->GetTileTilesetIndex(n, m);

				if (tilesetIndex != -1)
				{
					const Tmx::Tileset *tileSet = mMap->GetTileset(tilesetIndex);

					int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
					int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;

					Texture* texture = mListTileset[layer->GetTileTilesetIndex(n, m)];

					//tile index
					int tileID = layer->GetTileId(n, m);

					int y = tileID / tileSetWidth; // chỉ số của tileId trong tileset
					int x = tileID % tileSetWidth;

					sourceRECT.top = y * tileHeight;
					sourceRECT.bottom = sourceRECT.top + tileHeight;
					sourceRECT.left = x * tileWidth;
					sourceRECT.right = sourceRECT.left + tileWidth;

					//tru tilewidth/2 va tileheight/2 vi GameObject ve o vi tri giua hinh anh cho nen doi hinh de cho
					//dung toa do (0,0) cua the gioi thuc la (0,0) neu khong thi se la (-tilewidth/2, -tileheigth/2);
					FPOINT position(n * tileWidth + tileWidth / 2, m * tileHeight + tileHeight / 2);

					position.y = mapHeight - position.y; 
					/*
					Code demo xét theo hệ trục của màn hình với y hướng xuống. nên phải thiết lập lại độ cao cho tile trong map. 
					*/
					SpriteSpec* spriteSpec = new SpriteSpec();
					spriteSpec->setWidth(tileWidth);
					spriteSpec->setHeight(tileHeight);
					spriteSpec->setX(sourceRECT.left);
					spriteSpec->setY(sourceRECT.top);

					GameObject* sprite = new GameObject();
					sprite->setTexture(texture);
					sprite->setSpriteSpec(spriteSpec);
					sprite->setPostion(position);
					mapNode.push_back(sprite);
					//sprite->Draw(position, sourceRECT, D3DXVECTOR2());
				}
			}
		}
	}

	return mapNode;
}

void GameMap::parseObjectGroup(){
	for (int i = 0; i < mMap->GetNumObjectGroups(); ++i)
	{
		printf("                                    \n");
		printf("====================================\n");
		printf("Object group : %02d\n", i);
		printf("====================================\n");

		// Get an object group.
		const Tmx::ObjectGroup *objectGroup = mMap->GetObjectGroup(i);

		// Iterate through all objects in the object group.
		for (int j = 0; j < objectGroup->GetNumObjects(); ++j)
		{
			// Get an object.
			const Tmx::Object *object = objectGroup->GetObject(j);

			// new GameObject
			GameObject* gameObject = new GameObject();
			gameObject->setTexture(mObjectTexture);

			BOX collistionBox;
			collistionBox.x = object->GetX();
			collistionBox.y = object->GetY();
			collistionBox.width = object->GetWidth();
			collistionBox.height = object->GetHeight();
			gameObject->setCollisionBox(collistionBox);

			gameObject->setType(std::stoi(object->GetType()));
			
			mListObjet.push_back(gameObject);		
		}
	}

}