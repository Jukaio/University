// AI_Sheep_Component.cpp

#include "Components/AI_Sheep_Component.h"
#include <iostream>
#include "Components/Transform_Component.h"
#include "Components/Render_Component.h"
#include "Sheep.h"
#include "Grid/Grid.h"
#include "Wyvern_Game.h"
#include "Lehmer32.h"
#include <chrono>
#include "Mouse.h"
#include "Keyboard.h"

AI_Sheep_Component::AI_Sheep_Component(Sheep* game_object, float sense_rate, float decide_rate, float act_rate, Wyvern_Game* game)
	: AI_Component(game_object, sense_rate, decide_rate, act_rate)
	, sheep_(game_object)
	, game_(game)
	, node_(nullptr)
	, prev_Node_(nullptr)
	, next_Node_(nullptr)
{
	transform_ = sheep_->Get_Transform();
	grid_ = sheep_->Get_Grid();
}

AI_Sheep_Component::~AI_Sheep_Component()
{
}

void AI_Sheep_Component::On_Enable()
{
}

void AI_Sheep_Component::On_Disable()
{
}

Node* AI_Sheep_Component::Get_Current_Node()
{
	Vector2 grid_pos = transform_->Get_Position_With_Origin() / Grid::TILE_DIMENSION;
	return grid_->Get_Node(grid_pos);
}

Node* AI_Sheep_Component::Get_Next_Node()
{
	// Get random number with Lehmer32(); Seed is Run_Tíme + System_Time
	long int run_Time_Ticks = Service<Time>::Get()->Run_Time().As_Miliseconds();
	long int system_Time = (long int)std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	Lehmer::Set_Lehmer_Seed(system_Time);

	// Set Index
	int index = Lehmer::Lehmer32() % node_->Get_Neighbours().size();
	return node_->Get_Neighbours()[index];
}

void AI_Sheep_Component::Sense()
{
}

void AI_Sheep_Component::Decide()
{
}

void AI_Sheep_Component::Act()
{
	node_ = Get_Current_Node();
	if (next_Node_ == nullptr)
	{
		next_Node_ = Get_Next_Node();
	}


	if (Move_Towards(next_Node_->Get_Position_Centered_Origin()))
	{
		next_Node_ = Get_Next_Node();
	}

	if (node_ != prev_Node_)
	{
		if (prev_Node_ != nullptr)
			prev_Node_->has_Wolf_ = false;
		node_->has_Wolf_ = true;
	}

	prev_Node_ = node_;
}

bool AI_Sheep_Component::Move_Towards(Vector2 position)
{
	if (next_Node_ == node_)
		return true;

	Vector2 temp = transform_->Get_Position();
	Vector2 direction = position - temp;
	direction.Normalise();

	temp += direction;
	transform_->Set_Position(temp);

	return false;
}
