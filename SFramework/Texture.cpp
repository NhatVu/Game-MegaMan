#include "Texture.h"
#include "SFramework.h"
#include "rapidxml-1.13\rapidxml.hpp"
#include <fstream>
#include <vector>

using namespace s_framework;
using namespace rapidxml;

//Texture *Texture::m_instance = NULL;
Texture::Texture()
{
}

Texture::~Texture()
{
	for (auto const &ent : m_mapTexture){
		delete ent.second;
	}
}

//Texture* Texture::getInstance(){
//	if (m_instance == NULL)
//		m_instance = new Texture();
//	return m_instance;
//}


LPDIRECT3DTEXTURE9 Texture::getTexture()
{
	return m_texture;
}

SpriteSpec* Texture::getSpriteSpecById(int id)
{
	return m_mapTexture[id];
}

void Texture::loadImageToTexture(string imageSource)
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	result = D3DXGetImageInfoFromFileA(imageSource.c_str(), &info); //

	D3DXCreateTextureFromFileExA(
		SFramework::getInstance()->getDirect3DDevice(),
		imageSource.c_str(),
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255,255,255),
		&info,
		NULL,
		&m_texture);

	if (result != D3D_OK)
	{
		int i = 10;
	}
}

void Texture::parseTextureXMLFile(string xmlFile)
{
	xml_document<> doc;
	xml_node<> * root_node;
	// Read the xml file into a vector
	ifstream theFile(xmlFile);
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);
	// Find our root node
	root_node = doc.first_node();
	// Iterate over the brewerys

	SpriteSpec* t_spriteSpec = NULL;
	int id = 0;
	for (xml_node<> * sprite_node = root_node->first_node(); sprite_node; sprite_node = sprite_node->next_sibling())
	{
		t_spriteSpec = new SpriteSpec();

		id = stoi(sprite_node->first_attribute("n")->value());

		t_spriteSpec->setX(stoi(sprite_node->first_attribute("x")->value()));
		t_spriteSpec->setY(stoi(sprite_node->first_attribute("y")->value()));
		t_spriteSpec->setWidth(stoi(sprite_node->first_attribute("w")->value()));
		t_spriteSpec->setHeight(stoi(sprite_node->first_attribute("h")->value()));

		m_mapTexture[id] = t_spriteSpec;

	}
}

void Texture::init(string imageSource, string textureXML)
{
	loadImageToTexture(imageSource);
	parseTextureXMLFile(textureXML);
}

void Texture::init(string imageSource){
	loadImageToTexture(imageSource);
}