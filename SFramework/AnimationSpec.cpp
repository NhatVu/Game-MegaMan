#include "AnimationSpec.h"

using namespace s_framework;

AnimationSpec::AnimationSpec()
{
}


AnimationSpec::~AnimationSpec()
{
}

int AnimationSpec::getDelayTime()
{
	return m_delayTime;
}
void AnimationSpec::setDelayTime(int a)
{
	m_delayTime = a;
}

vector<SpriteSpec*> AnimationSpec::getSpriteSpecs()
{
	return m_spriteSpecs;
}

void AnimationSpec::setSpriteSpecs(vector<SpriteSpec*> a)
{
	m_spriteSpecs = a;
}
void AnimationSpec::addSpriteSpec(SpriteSpec* a)
{
	m_spriteSpecs.push_back(a);
}


void AnimationSpec::nextFrame(){
	int max_sprites = m_spriteSpecs.size();
	for (int i = 0; i < max_sprites; i++){
		if (i + 1 == max_sprites)
			m_currentIndex = 0;
		else
			m_currentIndex = i + 1;
	}
}
SpriteSpec* AnimationSpec::getCurrentSpriteSpec(){
	// get current sprite spec
	SpriteSpec* currentSprite = m_spriteSpecs[m_currentIndex];
	// get next sprite index
	nextFrame();

	return currentSprite;
}