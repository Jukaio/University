// World.cpp

#include "World.h"
#include <iostream>
#include "Player.h"
#include "Wyvern_Game.h"
#include "Grass.h"
#include "Wolf.h"
#include "Sheep.h"
#include "Components/Transform_Component.h"
#include "Lehmer32.h"
#include "Service.h"
#include "Time.h"
#include <chrono>

/* // Works too, but it is not alligning memory
Car** mycars = new Car*[userInput];
for (int i=0; i<userInput; i++){
	mycars[i] = new Car(...);
}

...

for (int i=0; i<userInput; i++){
	delete mycars[i];
}
delete [] mycars;
*/

World::World(Wyvern_Game* game)
	: game_(game)
{
	// Memory Alloc for X amount of sizeof()
	grass_Field_ = Grass::Alloc_Grass(Grid::HEIGHT_GRID * Grid::WIDTH_GRID);
	// Init array
	for (int x = 0; x < Grid::WIDTH_GRID; x++)
	{
		for (int y = 0; y < Grid::HEIGHT_GRID; y++)
		{
			// Insert new Element in Allocated Memory
			new(&grass_Field_[y * Grid::WIDTH_GRID + x])Grass(game, Vector2(x, y));
			grass_Field_[y * Grid::WIDTH_GRID + x].Disable();
		}
	}
	
	// Random grass location
	int x = Lehmer::Lazy_Lehmer32(Grid::WIDTH_GRID);
	int y = Lehmer::Lazy_Lehmer32(Grid::HEIGHT_GRID);

	//Activate grass at:
	Vector2 position = game->Get_Grid()->Get_Node(Vector2(x, y))->Get_Position();
	grass_Field_[0].Get_Transform()->Set_Position(position);
	grass_Field_[0].Enable();
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

	// Delete Array
	//for (int x = 0; x < Grid::WIDTH_GRID; x++)
	//{
	//	for (int y = 0; y < Grid::HEIGHT_GRID; y++)
	//	{
	//		grass_Field_[y * Grid::WIDTH_GRID + x].~Grass();
	//	}
	//}
	//operator delete[](grass_Field_);
	Grass::Dealloc_Grass(grass_Field_, Grid::HEIGHT_GRID * Grid::WIDTH_GRID);
}


void World::Add(Game_Object* obj)
{
	game_Objects_.push_back(obj);
}



Grass* World::Get_Grass_Field()
{
	return grass_Field_;
}


void World::Update()
{
	for (int i = 0; i < game_Objects_.size(); i++)
	{
		if (game_Objects_[i]->Get_Active() == true)
			game_Objects_[i]->Update();
	}

	for (Grass* grass = grass_Field_; grass < &grass_Field_[Grid::WIDTH_GRID * Grid::HEIGHT_GRID]; grass++)
	{
		if (grass->Get_Active())
			grass->Update();
	}
}

void World::Render()
{
	for (Grass* grass = grass_Field_; grass < &grass_Field_[Grid::WIDTH_GRID * Grid::HEIGHT_GRID]; grass++)
	{
		if (grass->Get_Active())
			grass->Render();
	}

	for (int i = 0; i < game_Objects_.size(); i++)
	{
		if (game_Objects_[i]->Get_Active() == true)
			game_Objects_[i]->Render();
	}
}

