//World.h

#ifndef __WORLD__
#define __WORLD__

#include <SDL.h>
#include "Grass.h"
#include <vector>


struct World
{
	static const int width_ = 900, height_ = 900;

	std::vector<Grass> grass_Entities_;
	
	void Create(Grid* grid, SDL_Renderer* renderer);

	void Add_Entity(Grass& AI_Enity);
	void Update();
	void Render();

};




#endif // !__WORLD__
