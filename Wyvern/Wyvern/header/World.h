// World.h

#ifndef __WORLD__
#define __WORLD__


#include <vector>
#include "Grass.h"
#include "Grid/Grid.h"

struct Wyvern_Game;


struct World
{
	Wyvern_Game* game_;

	World(Wyvern_Game* game);
	~World();

	void Add(Game_Object* obj); 
	Grass* Get_Grass_Field();

	void Update();
	void Render();

private:
	Grass* grass_Field_;

	std::vector<Game_Object*> game_Objects_;
};


#endif // !__WORLD__
