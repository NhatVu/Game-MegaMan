#include "AnimationManager.h"
#include <fstream>
#include <vector>
#include "../../MegaMan/MegaManUtilities.h"

#include <iostream>
#include <cstdio>
#include "../rapidjson/document.h"
#include "../rapidjson/filereadstream.h"

using namespace rapidjson;
using namespace std;
using namespace s_framework;

AnimationManager* AnimationManager::m_instance = NULL;

AnimationManager::AnimationManager()
{
	for (auto const &ent : m_mapStateToAnimation){
		delete ent.second;
	}
}


AnimationManager::~AnimationManager()
{
	for (auto const &ent1 : m_mapStateToAnimation){
		delete ent1.second;
	}
}

AnimationManager* AnimationManager::getInstance(){
	if (m_instance == NULL)
		m_instance = new AnimationManager();
	return m_instance;
}

void AnimationManager::resetResourceManager(){
	delete m_instance;
	m_instance = NULL;
}

void AnimationManager::parseAnimationJSON(Texture* texture,string jsonFile){
	FILE* pFile = fopen(jsonFile.c_str(), "rb");
	char buffer[65536];
	FileReadStream is(pFile, buffer, sizeof(buffer));
	Document document;
	//document.ParseStream<0, UTF8<>, FileReadStream>(is);
	document.ParseStream(is);
	Value& animation_list = document["animation"];

	SpriteSpec* t_spriteSpec = NULL;
	vector<SpriteSpec*> t_listSpriteSpec;

	ObjectState t_objectState;
	int objectType = 0;
	int stateID = 0;
	int frameID = 0;
	int delayFrame = 0;
	for (SizeType i = 0; i < animation_list.Size(); i++)
	{
		//t_spriteSpec = new SpriteSpec();
		Value& animation = animation_list[i];
		objectType = animation["characterID"].GetInt();
		Value& state = animation["state"];
		for (SizeType j = 0; j < state.Size(); j++){
			stateID = state[j]["stateID"].GetInt();
			delayFrame = state[j]["delayFrame"].GetInt();

			// gán characterID và stateID vào lớp CharacterState
			t_objectState.m_character = objectType;
			t_objectState.m_state = stateID;

			AnimationSpec* t_animationSpec = new AnimationSpec();
			t_animationSpec->setDelayFrame(delayFrame);
			//// biến tạm chứa list SpriteSpec
			vector<SpriteSpec*> t_listSpriteSpec;

			Value& frame = state[j]["frame"];
			for (SizeType f = 0; f < frame.Size(); f++){

				frameID = frame[f].GetInt();
				t_spriteSpec = texture->getSpriteSpecById(frameID);
				t_listSpriteSpec.push_back(t_spriteSpec);
			}
			t_animationSpec->setSpriteSpecs(t_listSpriteSpec);

			m_mapStateToAnimation[t_objectState] = t_animationSpec;
		}
	}
	
}

AnimationSpec* AnimationManager::getAnimationSprites(int character, int state)
{
	ObjectState t;
	t.m_character = character;
	t.m_state = state;

	return m_mapStateToAnimation[t];
}