#include "GameMap.h"
#include "../SpriteAndAnimation/SpriteSpec.h"
using namespace s_framework;

GameMap::GameMap(char* filePath, Texture* objectTexture)
{
	this->mObjectTexture = objectTexture;
	this->filePath = filePath;
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
	if (tileSetTexture != NULL)
		delete tileSetTexture;
}

//vector<Node*> GameMap::getNodesBackground(){
//	return mNodesBackground;
//}

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

//void GameMap::parseBackground()
//{
//	for (size_t i = 0; i < mMap->GetNumTileLayers(); i++)
//	{
//		const Tmx::TileLayer *layer = mMap->GetTileLayer(i);
//
//		if (!layer->IsVisible())
//		{
//			continue;
//		}
//
//		RECT sourceRECT;
//
//		int tileWidth = mMap->GetTileWidth();
//		int tileHeight = mMap->GetTileHeight();
//		int mapHeight = mMap->GetHeight() * tileHeight;
//
//
//		for (size_t m = 0; m < layer->GetHeight(); m++)
//		{
//			for (size_t n = 0; n < layer->GetWidth(); n++)
//			{
//				int tilesetIndex = layer->GetTileTilesetIndex(n, m);
//
//				if (tilesetIndex != -1)
//				{
//					const Tmx::Tileset *tileSet = mMap->GetTileset(tilesetIndex);
//
//					int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
//					int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;
//
//					Texture* texture = mListTileset[layer->GetTileTilesetIndex(n, m)];
//
//					//tile index
//					int tileID = layer->GetTileId(n, m);
//
//					int y = tileID / tileSetWidth; // chỉ số của tileId trong tileset
//					int x = tileID % tileSetWidth;
//
//					sourceRECT.top = y * tileHeight;
//					sourceRECT.bottom = sourceRECT.top + tileHeight;
//					sourceRECT.left = x * tileWidth;
//					sourceRECT.right = sourceRECT.left + tileWidth;
//
//				
//				//	FPOINT position(n * tileWidth + tileWidth / 2, m * tileHeight + tileHeight / 2);
//					FPOINT position(n * tileWidth, m * tileHeight);
//					position.y = mapHeight - position.y; // đây là tọa độ top-left của từng tile
//					/*
//					Code demo xét theo hệ trục của màn hình với y hướng xuống. nên phải thiết lập lại độ cao cho tile trong map.
//					*/
//					SpriteSpec* spriteSpec = new SpriteSpec();
//					spriteSpec->setWidth(tileWidth);
//					spriteSpec->setHeight(tileHeight);
//					spriteSpec->setX(sourceRECT.left);
//					spriteSpec->setY(sourceRECT.top);
//					
//					GameObject* sprite = new GameObject();
//					sprite->setTexture(texture);
//					sprite->setSpriteSpec(spriteSpec);
//					sprite->setPostion(position);
//					//sprite->render();
//					mNodesBackground.push_back(sprite);
//					//sprite->Draw(position, sourceRECT, D3DXVECTOR2());
//				}
//			}
//		}
//	}
//}

void GameMap::parseBackground(){
	// Read the xml file into a vector
	xml_node<> * m_rootNode;
	xml_document<> m_doc;
	ifstream theFile(filePath);
	if (theFile.fail())
		return;
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	m_doc.parse<0>(&buffer[0]);
	m_rootNode = m_doc.first_node("map");
	if (m_rootNode == NULL)
		return;

	// Parse map elements		
	int tileSetWidth = atoi(m_rootNode->first_attribute("tilewidth")->value()); // 1 tile rộng bao nhiêu
	int tileSetHeight = atoi(m_rootNode->first_attribute("tileheight")->value()); // 1 tile cao bao nhiêu
	int mapWidthCount = atoi(m_rootNode->first_attribute("width")->value()); // số lượng tile theo width trong map
	int mapHeightCount = atoi(m_rootNode->first_attribute("height")->value());
	this->mapHeight = tileSetHeight * mapHeightCount;
	//std::string orientation = m_rootNode->first_attribute("orientation")->value();
	//int viewporttype = atoi(m_rootNode->first_attribute("viewporttype")->value());
	//vector<int> rangeOfMovementData = vector<int>(20);
	//rangeOfMovementData.clear();
	//m_tileMap = new TileMap(tileWidth, tileHeight, width, height);
	//m_tileMap->SetViewportType(viewporttype);

	// Parse Tilesets elements
	int firstgid, dimensionX, dimensionY, tileSetWidthCount, tileSetHeightCount;
	string tileSetName, imageSourceName;
	for (xml_node<> * tileSetNode = m_rootNode->first_node("tileset"); tileSetNode;
		tileSetNode = tileSetNode->next_sibling("tileset"))
	{
		firstgid = atoi(tileSetNode->first_attribute("firstgid")->value());
		tileSetName = tileSetNode->first_attribute("name")->value();
		int columns = atoi(tileSetNode->first_attribute("columns")->value());
		int totalTileCount = atoi(tileSetNode->first_attribute("tilecount")->value());
		tileSetWidthCount = columns;
		tileSetHeightCount = totalTileCount / columns;

		xml_node<> * imageNode = tileSetNode->first_node("image");
		imageSourceName = imageNode->first_attribute("source")->value();


		std::string texturePath = imageSourceName;


		//Register texture
		tileSetTexture = new Texture();
		tileSetTexture->init("Resources\\" + texturePath); // chỉ load image vào texture
	}

	//Parse map data
	xml_node<> *mapLayer = m_rootNode->first_node("layer");
	string mapLayerName = mapLayer->first_attribute("name")->value();
	int mapLayerWidth = atoi(mapLayer->first_attribute("width")->value());
	int mapLayerHeight = atoi(mapLayer->first_attribute("height")->value());

	// Allocate mapdata
	/*int** mapData = new int*[mapLayerHeight];
	for(int i =0; i < mapLayerHeight; i++)
	mapData[i] = new int[mapLayerWidth];*/
	vector<int>* mapData = new vector<int>();
	xml_node<> * data = mapLayer->first_node("data");
	xml_node<> * tileNode;
	int tileIDInMap = 0;
	for (tileNode = data->first_node("tile"); tileNode; tileNode = tileNode->next_sibling())
	{
		int tileIDInTexture = atoi(tileNode->first_attribute("gid")->value());
		//tile index
		if (tileIDInTexture == 0){
			tileIDInMap++;
			continue;
		}
		tileIDInTexture--;
		int x = (tileIDInTexture % tileSetWidthCount) * tileSetHeight;
		int y = (tileIDInTexture / tileSetWidthCount) * tileSetWidth; // Tọa độ left-top của tileID trong texture

		RECT sourceRECT; // trong texture
		sourceRECT.left = x;
		sourceRECT.top = y;
		sourceRECT.bottom = sourceRECT.top + tileSetHeight;
		sourceRECT.right = sourceRECT.left + tileSetWidth;


		//	FPOINT position(n * tileWidth + tileWidth / 2, m * tileHeight + tileHeight / 2);
		int xInMap = (tileIDInMap % mapWidthCount) * tileSetWidth;
		int yInmap = (tileIDInMap / mapWidthCount) * tileSetHeight;

		FPOINT position(xInMap, yInmap);
		position.y = mapHeight - position.y; // đây là tọa độ top-left của từng tile
		/*
		Code demo xét theo hệ trục của màn hình với y hướng xuống. nên phải thiết lập lại độ cao cho tile trong map.
		*/
		SpriteSpec* spriteSpec = new SpriteSpec();
		spriteSpec->setWidth(tileSetWidth);
		spriteSpec->setHeight(tileSetHeight);
		spriteSpec->setX(sourceRECT.left);
		spriteSpec->setY(sourceRECT.top);

		GameObject* sprite = new GameObject();
		sprite->setTexture(tileSetTexture);
		sprite->setSpriteSpec(spriteSpec);
		sprite->setPostion(position);
		//sprite->render();
		//mNodesBackground.push_back(sprite);
		ObjectManager::getInstance()->getAllBackground()[tileIDInMap] = sprite;

		tileIDInMap++;
	}

}

//vector<Node*> GameMap::getScene(){
//
//	for (size_t i = 0; i < mMap->GetNumTileLayers(); i++)
//	{
//		const Tmx::TileLayer *layer = mMap->GetTileLayer(i);
//
//		if (!layer->IsVisible())
//		{
//			continue;
//		}
//
//		RECT sourceRECT;
//
//		int tileWidth = mMap->GetTileWidth();
//		int tileHeight = mMap->GetTileHeight();
//		int mapWidth = mMap->GetWidth() * tileWidth;
//		int mapHeight = mMap->GetHeight() * tileHeight;
//
//		for (size_t m = 0; m < layer->GetHeight(); m++)
//		{
//			for (size_t n = 0; n < layer->GetWidth(); n++)
//			{
//				int tilesetIndex = layer->GetTileTilesetIndex(n, m);
//
//				if (tilesetIndex != -1)
//				{
//					const Tmx::Tileset *tileSet = mMap->GetTileset(tilesetIndex);
//
//					int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
//					int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;
//
//					Texture* texture = mListTileset[layer->GetTileTilesetIndex(n, m)];
//
//					//tile index
//					int tileID = layer->GetTileId(n, m);
//
//					int y = tileID / tileSetWidth; // chỉ số của tileId trong tileset
//					int x = tileID % tileSetWidth;
//
//					sourceRECT.top = y * tileHeight;
//					sourceRECT.bottom = sourceRECT.top + tileHeight;
//					sourceRECT.left = x * tileWidth;
//					sourceRECT.right = sourceRECT.left + tileWidth;
//
//					//tru tilewidth/2 va tileheight/2 vi GameObject ve o vi tri giua hinh anh cho nen doi hinh de cho
//					//dung toa do (0,0) cua the gioi thuc la (0,0) neu khong thi se la (-tilewidth/2, -tileheigth/2);
//					FPOINT position(n * tileWidth + tileWidth / 2, m * tileHeight + tileHeight / 2);
//
//					position.y = mapHeight - position.y;
//					/*
//					Code demo xét theo hệ trục của màn hình với y hướng xuống. nên phải thiết lập lại độ cao cho tile trong map.
//					*/
//					SpriteSpec* spriteSpec = new SpriteSpec();
//					spriteSpec->setWidth(tileWidth);
//					spriteSpec->setHeight(tileHeight);
//					spriteSpec->setX(sourceRECT.left);
//					spriteSpec->setY(sourceRECT.top);
//
//					GameObject* sprite = new GameObject();
//					sprite->setTexture(texture);
//					sprite->setSpriteSpec(spriteSpec);
//					sprite->setPostion(position);
//					mapNode.push_back(sprite);
//					//sprite->Draw(position, sourceRECT, D3DXVECTOR2());
//				}
//			}
//		}
//	}
//
//	return mapNode;
//}

//void GameMap::parseObjectGroup(){
//	int mapHeight = mMap->GetHeight() * mMap->GetTileHeight();
//
//	for (int i = 0; i < mMap->GetNumObjectGroups(); ++i)
//	{
//		// Get an object group.
//		const Tmx::ObjectGroup *objectGroup = mMap->GetObjectGroup(i);
//
//		// Iterate through all objects in the object group.
//		for (int j = 0; j < objectGroup->GetNumObjects(); ++j)
//		{
//			// Get an object.
//			const Tmx::Object *object = objectGroup->GetObject(j);
//
//			// new GameObject
//			GameObject* gameObject = new GameObject();
//			gameObject->setTexture(mObjectTexture);
//
//			BOX collistionBox;
//			collistionBox.x = object->GetX();
//			collistionBox.y = mapHeight - object->GetY();
//			collistionBox.width = object->GetWidth();
//			collistionBox.height = object->GetHeight();
//			collistionBox.vx = 0.0f;
//			collistionBox.vy = 0.0f;
//			gameObject->setCollisionBox(collistionBox);
//
//			gameObject->setType(std::stoi(object->GetType()));
//
//			mListObjet.push_back(gameObject);
//		}
//	}
//
//}

void GameMap::parseObjectGroup(){
	// Parse object group
	xml_node<> * m_rootNode;
	xml_document<> m_doc;
	ifstream theFile(filePath);
	if (theFile.fail())
		return;
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	m_doc.parse<0>(&buffer[0]);
	m_rootNode = m_doc.first_node("map");
	if (m_rootNode == NULL)
		return;
	xml_node<> *objectLayer = m_rootNode->first_node("objectgroup");
	if (objectLayer != NULL)
	{
		xml_node<> *objectNode;
		//std::tr1::unordered_map<ObjectId, GameObject*>* m_objectHashTable = new std::tr1::unordered_map<ObjectId, GameObject*>();
		std::vector<GameObject*>* m_objectVector = new std::vector<GameObject*>(200);

		objectNode = objectLayer->first_node("object");
		for (objectNode = objectLayer->first_node("object"); objectNode; objectNode = objectNode->next_sibling())
		{

			int id = atoi(objectNode->first_attribute("id")->value());
			int objType = atoi(objectNode->first_attribute("type")->value());
			int x = atoi(objectNode->first_attribute("x")->value());
			int y = atoi(objectNode->first_attribute("y")->value());
			int width = atoi(objectNode->first_attribute("width")->value());
			int height = atoi(objectNode->first_attribute("height")->value());
			int objectType = atoi(objectNode->first_attribute("type")->value());
			//std::string objData = objectNode->first_attribute("data")->value();
			//int objDataInteger = atoi(objectNode->first_attribute("data")->value());

			// new GameObject
			GameObject* gameObject = new GameObject();
			gameObject->setObjectID(id);
			gameObject->setTexture(mObjectTexture);

			BOX collistionBox;
			collistionBox.x = x;
			collistionBox.y = mapHeight - y;
			collistionBox.width = width;
			collistionBox.height = height;
			collistionBox.vx = 0.0f;
			collistionBox.vy = 0.0f;
			gameObject->setCollisionBox(collistionBox);

			gameObject->setType(objectType);

			//mListObjet.push_back(gameObject);
			ObjectManager::getInstance()->getAllObject()[id] = gameObject;
		}
	}
}
