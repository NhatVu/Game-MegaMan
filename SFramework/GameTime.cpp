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

void GameTime::setCurrentTime()
{
	mCurrentTime = GetTickCount();
	mDeltaTime = mCurrentTime - mStartTime;
}
DWORD GameTime::getDeltaTime()
{
	return mDeltaTime;
}

DWORD GameTime::getTimePerFrame()
{
	return 1.0f / (FPS*1000);
}

DWORD GameTime::getTimeSleep()
{
	return (1.0f / (FPS*1000) - (mCurrentTime - mStartTime));
}
