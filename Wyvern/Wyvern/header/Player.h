// Player.h

#ifndef __PLAYER__
#define __PLAYER__

#include "Game_Object.h"

struct Player : Game_Object
{
	Player();
	~Player();

	void Update();
	void Render();
};


#endif // !__PLAYER__
