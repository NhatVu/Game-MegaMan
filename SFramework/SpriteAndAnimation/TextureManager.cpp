#include "TextureManager.h"
#include "../SFramework.h"
#include "../rapidxml-1.13\rapidxml.hpp"
#include <fstream>
#include <vector>


using namespace s_framework;
using namespace rapidxml;

//TextureManager* TextureManager::mInstance = NULL;
Texture* TextureManager::objectTexture = NULL;
TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
	/*for (auto const &ent : mTextureMap) {
		delete ent.second;
	}*/
}

//TextureManager * s_framework::TextureManager::getInstance()
//{
//	if (mInstance == NULL)
//	{
//		mInstance = new TextureManager();
//	}
//
//	return mInstance;
//}
//
//void s_framework::TextureManager::setTextureMap()
//{
//	xml_document<> doc;
//	xml_node<> * root_node;
//	// Read the xml file into a vector
//	ifstream theFile(SOURCE_TEXTURE_XML);
//	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
//	buffer.push_back('\0');
//	// Parse the buffer using the xml file parsing library into doc 
//	doc.parse<0>(&buffer[0]);
//	// Find our root node
//	root_node = doc.first_node();
//	// Iterate over the brewerys
//
//	SpriteSpec* t_spriteSpec = NULL;
//	int id = 0;
//	for (xml_node<> * sprite_node = root_node->first_node(); sprite_node; sprite_node = sprite_node->next_sibling())
//	{
//		t_spriteSpec = new SpriteSpec();
//
//		id = stoi(sprite_node->first_attribute("n")->value());
//
//		t_spriteSpec->setX(stoi(sprite_node->first_attribute("x")->value()));
//		t_spriteSpec->setY(stoi(sprite_node->first_attribute("y")->value()));
//		t_spriteSpec->setWidth(stoi(sprite_node->first_attribute("w")->value()));
//		t_spriteSpec->setHeight(stoi(sprite_node->first_attribute("h")->value()));
//
//		mTextureMap[id] = t_spriteSpec;
//	}
//}
//
//void s_framework::TextureManager::setTexture(LPDIRECT3DTEXTURE9 texture, string src)
//{
//	D3DXIMAGE_INFO info;
//	HRESULT result;
//
//	
//	result = D3DXGetImageInfoFromFileA(src.c_str(), &info); //
//
//	D3DXCreateTextureFromFileExA(
//		SFramework::getInstance()->getDirect3DDevice(),
//		src.c_str(),
//		info.Width,
//		info.Height,
//		1,
//		D3DUSAGE_DYNAMIC,
//		D3DFMT_UNKNOWN,
//		D3DPOOL_DEFAULT,
//		D3DX_DEFAULT,
//		D3DX_DEFAULT,
//		D3DCOLOR_XRGB(255, 255, 255),
//		&info,
//		NULL,
//		&texture);
//
//	if (result != D3D_OK)
//	{
//		int i = 10;
//	}
//}
//
//void s_framework::TextureManager::setObjectTexture()
//{
//	string fileName(SOURCE_TEXTURE_PNG);
//	setTexture(mObjectTexture, fileName);
//}
//
//void s_framework::TextureManager::setMapTexture()
//{
//	string fileName(SOURCE_MAP_PNG);
//	setTexture(mObjectTexture, fileName);
//}
//
//LPDIRECT3DTEXTURE9 s_framework::TextureManager::getObjectTexture()
//{
//	if (mObjectTexture == NULL)
//	{
//		setObjectTexture();
//	}
//
//	return mObjectTexture;
//}
//
//LPDIRECT3DTEXTURE9 s_framework::TextureManager::getObjectTexture()
//{
//	if (mMapTexture == NULL)
//	{
//		setMapTexture();
//	}
//
//	return mMapTexture;
//}
//
//SpriteSpec * s_framework::TextureManager::getSpriteSpecById(int id)
//{
//	if (mTextureMap.empty())
//	{
//		setTextureMap();
//	}
//	
//	return mTextureMap[id];
//}
//
