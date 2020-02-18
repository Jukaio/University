// Player.h

#ifndef __PLAYER__
#define __PLAYER__

#include "Game_Object.h"

struct Player : Game_Object
{
	Player();
	Player(Vector2 position, Vector2 size);
	Player(Vector2 position, float w, float h);
	Player(float x, float y, Vector2 size);
	Player(float x, float y, float w, float h);
	Player(int x, int y, int w, int h);

	void Update() final;
	
};


#endif // !__PLAYER__
