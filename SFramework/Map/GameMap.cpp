#include "GameMap.h"
#include "../SpriteAndAnimation/SpriteSpec.h"
#include "ObjectFactory.h"
#include "../SpriteAndAnimation/TextureManager.h"
#include "../../MegaMan/GameObject/Suzy.h"
using namespace s_framework;

GameMap::GameMap(char* filePath)
{
	this->filePath = filePath;
	parseBackground();
	parseObjectGroup();
}

GameMap::~GameMap()
{
}

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
		int yInMap = (tileIDInMap / mapWidthCount) * tileSetHeight;

		FPOINT position(xInMap, yInMap);
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
		sprite->setTexture(TextureManager::getInstance()->getMapTexture());
		sprite->setSpriteSpec(spriteSpec);
		sprite->setPostion(position);
		BOX collistionBox;
		collistionBox.x = xInMap;
		collistionBox.y = mapHeight - yInMap;
		collistionBox.width = tileSetWidth;
		collistionBox.height = tileSetHeight;
		collistionBox.vx = 0.0f;
		collistionBox.vy = 0.0f;
		sprite->setCollisionBox(collistionBox);
		//sprite->render();
		//mNodesBackground.push_back(sprite);
		ObjectManager::getInstance()->getAllBackground()[tileIDInMap] = sprite;

		tileIDInMap++;
	}

}


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
			string name = "";
			//try{
			if (objectNode->first_attribute("data") == NULL){
				int a = 5;
			}

			/*}
			catch ()*/

			//std::string objData = objectNode->first_attribute("data")->value();
			//int objDataInteger = atoi(objectNode->first_attribute("data")->value());

			// new GameObject
			GameObject* gameObject = ObjectFactory::createObject(objType);
			gameObject->setObjectID(id);
			gameObject->setTexture(TextureManager::getInstance()->getObjectTexture());
			gameObject->setType(objectType);

			BOX collistionBox;
			collistionBox.x = x;
			collistionBox.y = mapHeight - y;
			collistionBox.width = width;
			collistionBox.height = height;
			collistionBox.vx = 0.0f;
			collistionBox.vy = 0.0f;
			gameObject->setCollisionBox(collistionBox);
			gameObject->setPostion(FPOINT(collistionBox.x, collistionBox.y));
			gameObject->setInitPosition(FPOINT(collistionBox.x, collistionBox.y));

			// custom property
			if (objectType == ECharacter::BLASTER){
				int direction = atoi(objectNode->first_node("properties")->first_node("property")->first_attribute("value")->value());
				if (direction == 1)
					// default : từ phải sang trái
					gameObject->setFlipVertical(1);
				else if (direction == -1)
					gameObject->setFlipVertical(-1);
			}
			else if (objectType == ECharacter::SUZY){
				int direction = atoi(objectNode->first_node("properties")->first_node("property")->first_attribute("value")->value());
				((Suzy*)gameObject)->setDirection(direction);
				if (direction == 1)
					gameObject->setVelocity(FPOINT(-SUZY_VELOCITY, 0.0f));
				else gameObject->setVelocity(FPOINT(0.0f, -SUZY_VELOCITY));
			}
			//mListObjet.push_back(gameObject);
			ObjectManager::getInstance()->getAllObject()[id] = gameObject;
		}
	}
}
