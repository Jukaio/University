// World.h

#ifndef __WORLD__
#define __WORLD__

#include "Game_Object.h"
#include "Wyvern_Array.h"

struct World
{
	World();

	Wyvern_Array<Game_Object> game_Objects_;

	void Add(const Game_Object& obj);

	void Update();
	void Render(SDL_Renderer* renderer);

};


#endif // !__WORLD__
