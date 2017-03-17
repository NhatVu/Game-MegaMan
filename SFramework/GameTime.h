#ifndef _GAME_TIME_H_
#define _GAME_TIME_H_

#include <Windows.h>
namespace s_framework
{
	class GameTime
	{
	private:
		static GameTime *mTimeInstance;
		DWORD mStartTime;
		DWORD mDeltaTime;
		DWORD mCurrentTime;
		GameTime();

	public:

		static GameTime* getInstance();
		void setStartTime();
		void setCurrentTime();
		DWORD getDeltaTime();
		DWORD getTimePerFrame();
		DWORD getTimeSleep();
		~GameTime();
	};
}
#endif
