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
	void Set_Player(Game_Object* player);
	Game_Object* Get_Player();
	std::vector<Game_Object*>& Get_Game_Objects();

private:
	Game_Object* player_;
	std::vector<Game_Object*> game_Objects_;

};


#endif // !__WORLD__
