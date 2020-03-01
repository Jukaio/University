// World.h

#ifndef __WORLD__
#define __WORLD__

#include "Game_Object.h"
#include <vector>

struct World
{
	World();

	void Add(Game_Object* obj);

	void Update();
	void Render();
	std::vector<Game_Object*>& Get_Game_Objects();

private:
	std::vector<Game_Object*> game_Objects_;

};


#endif // !__WORLD__
