#include "SpriteSpec.h"
#include <time.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>

using namespace s_framework;
using namespace std;
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

void s_framework::SpriteSpec::random(int maxWidth, int maxHeight)
{
	this->x = rand() % maxWidth;
	this->y = rand() % maxHeight;
	this->width = rand() % maxWidth;
	this->height = rand() % maxHeight;
}
