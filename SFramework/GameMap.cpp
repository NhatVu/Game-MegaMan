﻿#include "GameMap.h"
#include "SpriteSpec.h"
using namespace s_framework;

GameMap::GameMap(){

}
GameMap::GameMap(char* filePath)
{
	
	LoadMap(filePath);
}

GameMap::~GameMap()
{
	for (auto const &ent1 : mListTileset){
		delete ent1.second;
	}

	for (int i = 0; i < mapNode.size(); i++){
		delete mapNode[i];
	}

	mapNode.clear();
	delete mMap;
}

void GameMap::LoadMap(char* filePath)
{
	mMap = new Tmx::Map();
	mMap->ParseFile(filePath);

	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = this->GetWidth();
	r.bottom = this->GetHeight();

	for (size_t i = 0; i < mMap->GetNumTilesets(); i++)
	{
		const Tileset *tileset = mMap->GetTileset(i);

		Texture *texture = new Texture();
		texture->init(tileset->GetImage()->GetSource());

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

void GameMap::Draw()
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

					//tru tilewidth/2 va tileheight/2 vi Sprite ve o vi tri giua hinh anh cho nen doi hinh de cho
					//dung toa do (0,0) cua the gioi thuc la (0,0) neu khong thi se la (-tilewidth/2, -tileheigth/2);
					FPOINT position(n * tileWidth + tileWidth / 2, m * tileHeight + tileHeight / 2);

					SpriteSpec* spriteSpec = new SpriteSpec();
					spriteSpec->setWidth(tileWidth);
					spriteSpec->setHeight(tileHeight);
					spriteSpec->setX(sourceRECT.left);
					spriteSpec->setY(sourceRECT.top);
					
					Sprite* sprite = new Sprite();
					sprite->setTexture(texture);
					sprite->setSpriteSpec(spriteSpec);
					sprite->setPostion(position);
					sprite->render();
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

					//tru tilewidth/2 va tileheight/2 vi Sprite ve o vi tri giua hinh anh cho nen doi hinh de cho
					//dung toa do (0,0) cua the gioi thuc la (0,0) neu khong thi se la (-tilewidth/2, -tileheigth/2);
					FPOINT position(n * tileWidth + tileWidth / 2, m * tileHeight + tileHeight / 2);

					SpriteSpec* spriteSpec = new SpriteSpec();
					spriteSpec->setWidth(tileWidth);
					spriteSpec->setHeight(tileHeight);
					spriteSpec->setX(sourceRECT.left);
					spriteSpec->setY(sourceRECT.top);

					Sprite* sprite = new Sprite();
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