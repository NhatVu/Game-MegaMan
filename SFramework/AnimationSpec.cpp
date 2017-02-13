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