//World.cpp

#include "World.h"


void World::Create(Grid* grid, SDL_Renderer* renderer)
{
	Grass grass;
	grass.Create(grid, renderer, this, 90, 90, 0.00f, 0.00f);
	grass_Entities_.push_back(grass);
}

void World::Add_Entity(Grass& AI_Entity)
{
	grass_Entities_.push_back(AI_Entity);
	
}

void World::Update()
{
	for (auto&& entity : grass_Entities_)
	{
		entity.Update();
	}

}

void World::Render()
{
	for (auto&& entity : grass_Entities_)
	{
		entity.Render();
	}
}