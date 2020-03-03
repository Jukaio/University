// World.cpp

#include "World.h"
#include <iostream>
#include "Player.h"


World::World()
{
	Add(new Player());
}

World::~World()
{
	for (auto&& game_object : game_Objects_)
	{
		if (game_object != nullptr)
			delete game_object;
		game_object = nullptr;
	}
	game_Objects_.clear();
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

