#include "AnimationSpec.h"
#include <algorithm>
using namespace s_framework;

AnimationSpec::AnimationSpec()
{
}


AnimationSpec::~AnimationSpec()
{
	using Iter = std::vector<GameObject*>::const_iterator;
	for (int i = 0; i < m_spriteSpecs.size(); i++){
		delete m_spriteSpecs[i];
	}
	m_spriteSpecs.clear();
}

int AnimationSpec::getDelayFrame()
{
	return m_delayFrame;
}
void AnimationSpec::setDelayFrame(int a)
{
	m_delayFrame = a;
	currentDelay = a;
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
	if (m_currentIndex < max_sprites - 1)
		m_currentIndex++;
	else{
		m_currentIndex = 0;
	}

}
SpriteSpec* AnimationSpec::getCurrentSpriteSpec(){
	// get current sprite spec
	SpriteSpec* currentSprite = m_spriteSpecs[m_currentIndex];
	// get next sprite index
	if (currentDelay == 0){
		nextFrame();
		currentDelay = m_delayFrame;
	}
	else
		currentDelay--;


	return currentSprite;
}

void AnimationSpec::reverseAnimation(){
	std::reverse(m_spriteSpecs.begin(), m_spriteSpecs.end());
}