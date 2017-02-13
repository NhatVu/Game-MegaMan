#include "GameTime.h"
#include "SFramework.h"

using namespace s_framework;

GameTime *GameTime::mTimeInstance = NULL;

GameTime::GameTime()
{
	mDeltaTime = 0;
	mStartTime = 0;
}


GameTime::~GameTime()
{
}

GameTime* GameTime::getInstance(){
	if (mTimeInstance == NULL)
		mTimeInstance = new GameTime();
	return mTimeInstance;
}

void GameTime::setStartTime(){
	mStartTime = GetTickCount();
}

void GameTime::setEndTime()
{
	mDeltaTime = GetTickCount() - mStartTime;
}
DWORD GameTime::getDeltaTime()
{
	return mDeltaTime;
}

DWORD GameTime::getTimePerFrame()
{
	return 1000 / FPS;
}

DWORD GameTime::getTimeSleep()
{
	return (1000 / FPS - (GetTickCount() - mStartTime));
}
