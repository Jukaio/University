// AI_Grass_Component.cpp

#include "Components/AI_Grass_Component.h"
#include <iostream>
#include "Components/Transform_Component.h"
#include "Components/Render_Component.h"
#include "Grass.h"
#include "Grid/Grid.h"
#include "Wyvern_Game.h"
#include "Lehmer32.h"
#include <chrono>
#include "Mouse.h"
#include "Keyboard.h"

/* 
- POOL THE OBJECTS
- Put object in OpenList/Vector if it gets activated
- Put object in losedList/Vector if it gets deactivated
*/

AI_Grass_Component::AI_Grass_Component(Grass* game_object, float sense_rate, float decide_rate, float act_rate, Wyvern_Game* game)
	: AI_Component(game_object, sense_rate, decide_rate, act_rate)
	, grass_(game_object)
	, game_(game)
	, spread_Rate_(4.0f)
	, spread_Timer_(spread_Rate_)
	, grow_Rate_(0.5f)
	, grow_Timer_(grow_Rate_)
	, level_(0)
	, max_Level_(5)
	, node_(nullptr)
{
	transform_ = grass_->Get_Transform();
	grid_ = grass_->Get_Grid();
}

AI_Grass_Component::~AI_Grass_Component()
{

}

void AI_Grass_Component::Sense()
{

}

void AI_Grass_Component::Decide()
{

}

void AI_Grass_Component::Act()
{
	node_ = Get_Current_Node();
	node_->has_Grass_ = true;

	if (AI_Component::Cooldown(spread_Timer_, spread_Rate_) && level_ == max_Level_)
		Spread();

	if (AI_Component::Cooldown(grow_Timer_, grow_Rate_))
		Grow();

	Vector2 mouse_Pos = Grid::Global_To_Grid(Service<Mouse>::Get()->Get_Mouse_Position());
	Vector2 node_Pos = Grid::Global_To_Grid(node_->Get_Position());

	if (mouse_Pos == node_Pos && Service<Keyboard>::Get()->Key_Pressed(SDL_SCANCODE_SPACE))
		grass_->Disable();
}

Node* AI_Grass_Component::Get_Current_Node()
{
	Vector2 grid_pos = transform_->Get_Position() / Grid::TILE_DIMENSION;
	return grid_->Get_Node(grid_pos);
}

void AI_Grass_Component::Spread()
{
	//Get random number with Lehmer32(); Seed is Run_Tíme + System_Time
	long int run_Time_Ticks = Service<Time>::Get()->Run_Time().As_Miliseconds();
	long int system_Time = (long int)std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	Lehmer::Set_Lehmer_Seed(run_Time_Ticks + system_Time);

	int index;
	int prev_index = Lehmer::Lehmer32() % node_->Get_Neighbours().size();
	for (int i = 0; i < node_->Get_Neighbours().size(); i++)
	{
		do {
			index = Lehmer::Lehmer32() % node_->Get_Neighbours().size();  //Get random number with Lehmer32(); Seed is Run_Time
		} while (index == prev_index);

		if (node_->Get_Neighbours()[index]->has_Grass_ != true)
		{
			// Use Object pool
			Grass* temp;
			for (Grass* grass = game_->Get_World()->Get_Grass_Field(); grass < &game_->Get_World()->Get_Grass_Field()[Grid::WIDTH_GRID * Grid::HEIGHT_GRID]; grass++)
			{
				if (grass->Get_Active() == false)
				{
					temp = grass;
					node_->Get_Neighbours()[index]->has_Grass_ = true;
					temp->Get_Transform()->Set_Position(node_->Get_Neighbours()[index]->Get_Position());
					//game_->Get_World()->Add_Grass(temp); // <- Only needed if you use "new Grass(grame_)", not needed for pool cause objects are already in vector
					temp->Set_Active(true);
					break;
				}
			}

			//for (int j = 0; j < game_->Get_World()->Get_Grass_Field().size(); j++)
			//{
			//	if (game_->Get_World()->Get_Grass_Field()[j]->Get_Active() == false)
			//	{
			//		temp = game_->Get_World()->Get_Grass_Field()[j];
			//		break;
			//	}
			//}
			if (&temp == nullptr)
				assert(false);

			//node_->Get_Neighbours()[index]->has_Grass_ = true;
			//temp->Get_Transform()->Set_Position(node_->Get_Neighbours()[index]->Get_Position());
			////game_->Get_World()->Add_Grass(temp); // <- Only needed if you use "new Grass(grame_)", not needed for pool cause objects are already in vector
			//temp->Set_Active(true);
			return;
		}
		prev_index = index;
	}
}

void AI_Grass_Component::Grow()
{
	Render_Component* render = grass_->Get_Render();
	if (render == nullptr)
		assert(true);

	render->Set_Next_Frame(0, 192, Render_Component::ONCE);
	if (level_ < max_Level_)
		level_++;
	node_->grass_Level_ = level_;
}

void AI_Grass_Component::On_Enable()
{
}

void AI_Grass_Component::On_Disable()
{
	if (node_ != nullptr)
	{
		node_->has_Grass_ = false;
		node_->grass_Level_ = 0;
		grass_->Get_Render()->Set_Next_Frame(0, 192, Render_Component::RESET);
	}
	level_ = 0;
}