//Grass.cpp

#include "Grass.h"
#include "Time.h"
#include <iostream>
#include "World.h"

void Grass::Create(Grid* grid, SDL_Renderer* renderer, World* world, int x, int y, float tick_Rate_Sense, float tick_Rate_Decide)
{
	AI_Entity::Create(grid, renderer, x, y, tick_Rate_Sense, tick_Rate_Decide);

	this->Set_Colour(0, 0, 0, 255);

	world_ = world;
	//int x_Index = (int)x_;
	//int y_Index = (int)y_;

	//Tile* temp = grid_->Get_Tile(x_Index, y_Index);
	//if (temp->grass_Level_ == 0)
	//	temp->grass_Level_++;
}

void Grass::Sense()
{
	//int x_Index = (int)x_;
	//int y_Index = (int)y_;
	//
	//Tile* temp = grid_->Get_Tile(x_Index + 1, y_Index);
}

void Grass::Decide()
{
	if (colour_.g < 250)
		current_State = State::GROW;
	else if (colour_.g >= 250 && expanded == false)
		current_State = State::EXPAND;
	else
		current_State = State::ROOT;
}


void Grass::Act()
{
	Update_Timer(expand_Timer_, expand_Interval_ );
	Update_Timer(grow_Timer_, grow_Interval_);

	switch (current_State)
	{
		case State::ROOT:

			break;

		case State::GROW:
			if (grow_Timer_ < 0 && colour_.g < 255)
			{
				colour_.g += Time::Get_Delta_Time().tick_Rate_;
				this->Set_Colour(colour_.r, colour_.g, colour_.b, 255);
			}
			break;

		case State::EXPAND:
			if (expand_Timer_ < 0 && expanded == false)
			{
				expanded = true;
				Expand();
			}
			break;

	}
}

void Grass::Expand()
{
	Grass grass;
	grass.Create(grid_, renderer_, world_, x_ + 90, y_, 5.0f, 5.0f);
	world_->Add_Entity(grass);
}
