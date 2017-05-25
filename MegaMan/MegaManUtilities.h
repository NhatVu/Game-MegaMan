#ifndef _MARIO_UTILITIES_H_
#define _MARIO_UTILITIES_H_

//#define GRAVITATIONAL_ACCELERATION 0.000f
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 256
enum ECharacter
{
	STATIC = 0,
	LADDER = 1,
	MEGAMAN_BULLET = 2,
	KAMADOMA = 3,
	MEGAMAN = 10,

};

enum EState
{
	IDLE = 1,
	RUNNING = 2,
	CLIMB = 3,
	JUMP = 4,
	DIE = 5,
	CLIMB_IDLE = 6,
	IDLE_FIRE = 7,
	ACTIVE = 8,
	JUMP_FIRE = 9,
};



#endif // !_MARIO_UTILITIES_H_

