// World.cpp

#include "World.h"
#include <iostream>
#include "Player.h"

World::World()
	:player_(nullptr)
{
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

void World::Set_Player(Game_Object* player)
{
	player_ = player;
}

Game_Object* World::Get_Player()
{
	return player_;
}

std::vector<Game_Object*>& World::Get_Game_Objects()
{
	return game_Objects_;
}


