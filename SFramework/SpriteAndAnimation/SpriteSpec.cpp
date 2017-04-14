#include "SpriteSpec.h"

using namespace s_framework;

SpriteSpec::SpriteSpec()
{
}


SpriteSpec::~SpriteSpec()
{
}


float SpriteSpec::getX()
{
	return x;
}
void SpriteSpec::setX(float a)
{
	x = a;
}

float SpriteSpec::getY()
{
	return y;
}
void SpriteSpec::setY(float a)
{
	y = a;
}

float SpriteSpec::getHeight()
{
	return height;
}
void SpriteSpec::setHeight(float a)
{
	height = a;
}

float SpriteSpec::getWidth()
{
	return width;
}
void SpriteSpec::setWidth(float a){
	width = a;
}