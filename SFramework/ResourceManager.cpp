#include "ResourceManager.h"
#include "rapidxml-1.13\rapidxml.hpp"
#include <fstream>
#include <vector>
#include "../MegaMan/MarioUtilities.h"

using namespace rapidxml;
using namespace s_framework;

ResourceManager* ResourceManager::m_instance = NULL;

ResourceManager::ResourceManager()
{
	
}


ResourceManager::~ResourceManager()
{
}

ResourceManager* ResourceManager::getInstance(){
	if (m_instance == NULL)
		m_instance = new ResourceManager();
	return m_instance;
}

void ResourceManager::resetResourceManager(){
	delete m_instance;
	m_instance = NULL;
}

void ResourceManager::parseAnimationXML(string xmlFile)
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
	vector<SpriteSpec*> t_listSpriteSpec;

	ObjectState t_objectState;
	int objectType = 0;
	int stateID = 0;
	int frameID = 0;
	int delayTime = 0;
	for (xml_node<> * character_node = root_node->first_node(); character_node; character_node = character_node->next_sibling())
	{
		//t_spriteSpec = new SpriteSpec();

		objectType = stoi(character_node->first_attribute("objectID")->value());

		for (xml_node<>* state_node = character_node->first_node(); state_node; state_node = state_node->next_sibling()){
			stateID = stoi(state_node->first_attribute("stateID")->value());
			delayTime = stoi(state_node->first_attribute("delayTime")->value());

			// gán characterID và stateID vào lớp CharacterState
			t_objectState.m_objectType = objectType;
			t_objectState.m_state = stateID;

			AnimationSpec* t_animationSpec = new AnimationSpec();
			t_animationSpec->setDelayTime(delayTime);
			//// biến tạm chứa list SpriteSpec
			vector<SpriteSpec*> t_listSpriteSpec;

			for (xml_node<>* frame_node = state_node->first_node(); frame_node; frame_node = frame_node->next_sibling()){

				frameID = stoi(frame_node->value());

				t_spriteSpec = Texture::getInstance()->getSpriteSpecById(frameID);
				t_listSpriteSpec.push_back(t_spriteSpec);
			}
			t_animationSpec->setSpriteSpecs(t_listSpriteSpec);

			m_mapAnimationToListSprite[t_objectState] = t_animationSpec;
		}
	}
}
//list<SpriteSpec*> ResourceManager::getListSprteOfAnimation(ECharacter character, EState state)
//{
//	CharacterState t;
//	t.m_character = character;
//	t.m_state = state;
//
//	return m_mapAnimationToListSprite[t];
//}