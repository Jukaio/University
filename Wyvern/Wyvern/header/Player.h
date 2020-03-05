// Player.h

#ifndef __PLAYER__
#define __PLAYER__

#include "Game_Object.h"

struct Wyvern_Game;

struct Player : Game_Object
{
	Wyvern_Game* game_;

	Player(Wyvern_Game* game);
	~Player();

	void Update();
	void Render();
};


#endif // !__PLAYER__
