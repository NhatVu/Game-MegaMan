#include "SpriteSpec.h"

using namespace s_framework;

SpriteSpec::SpriteSpec()
{
}


SpriteSpec::~SpriteSpec()
{
}


int SpriteSpec::getX()
{
	return x;
}
void SpriteSpec::setX(int a)
{
	x = a;
}

int SpriteSpec::getY()
{
	return y;
}
void SpriteSpec::setY(int a)
{
	y = a;
}

int SpriteSpec::getHeight()
{
	return height;
}
void SpriteSpec::setHeight(int a)
{
	height = a;
}

int SpriteSpec::getWidth()
{
	return width;
}
void SpriteSpec::setWidth(int a){
	width = a;
}