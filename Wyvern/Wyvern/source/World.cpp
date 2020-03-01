// World.cpp

#include "World.h"
#include <iostream>
#include "Player.h"

World::World()
{
	Add(new Game_Object());
}


void World::Add(Game_Object* obj)
{
	game_Objects_.push_back(obj);
}


void World::Update()
{
	for (int i = 0; i < game_Objects_.size(); i++)
	{
		game_Objects_[i]->Update();
	}
}

void World::Render()
{
	for (int i = 0; i < game_Objects_.size(); i++)
	{
		game_Objects_[i]->Render();
	}
}


std::vector<Game_Object*>& World::Get_Game_Objects()
{
	return game_Objects_;
}


