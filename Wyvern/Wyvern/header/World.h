// World.h

#ifndef __WORLD__
#define __WORLD__

#include "Game_Object.h"

struct World
{
	World();

	Game_Object* game_Objects_;
	int size_;

	void Add(Game_Object obj);


};


#endif // !__WORLD__
