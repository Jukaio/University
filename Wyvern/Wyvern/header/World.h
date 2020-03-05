// World.h

#ifndef __WORLD__
#define __WORLD__

#include "Game_Object.h"
#include <vector>

struct Wyvern_Game;

struct World
{
	Wyvern_Game* game_;

	World(Wyvern_Game* game);
	~World();

	void Add(Game_Object* obj);

	void Update();
	void Render();

private:
	std::vector<Game_Object*> game_Objects_;

};


#endif // !__WORLD__
