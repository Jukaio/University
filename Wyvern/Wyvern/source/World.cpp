// World.cpp

#include "World.h"

World::World()
{
}

void World::Add(const Game_Object& obj)
{
	game_Objects_.Push_Back(obj);
}



void World::Update()
{
	for (int i = 0; i < game_Objects_.Length(); i++)
	{
		game_Objects_[i]->Update();
	}
}

void World::Render(SDL_Renderer* renderer)
{
	for (int i = 0; i < game_Objects_.Length(); i++)
	{
		game_Objects_[i]->Render(renderer);
	}
}


