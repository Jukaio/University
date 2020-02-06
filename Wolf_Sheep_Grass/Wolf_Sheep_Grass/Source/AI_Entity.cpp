//AI_Entity.cpp

#include "iostream"
#include "AI_Entity.h"
#include "Time.h"

AI_Entity::AI_Entity()
	: x_(0)
	, y_(0)
	, s_tick_Rate_(0.0f)
	, d_tick_Rate_(0.0f)
	, s_Timer_(0.0f)
	, d_Timer_(0.0f)
	, grid_(nullptr)
	, renderer_(nullptr)
	, colour_({0, 0, 0, 0})
{

}

void AI_Entity::Create(Grid* grid, SDL_Renderer* renderer, int x, int y, float tick_Rate_Sense, float tick_Rate_Decide)
{
	x_ = (float) x;
	y_ = (float) y;
	s_tick_Rate_ = tick_Rate_Sense;
	d_tick_Rate_ = tick_Rate_Decide;
	renderer_ = renderer;
	grid_ = grid;

}

void AI_Entity::Update()
{
	Update_Timer(s_Timer_, s_tick_Rate_);
	Update_Timer(d_Timer_, d_tick_Rate_);

	if (s_Timer_ < 0)
		Sense();
	if (d_Timer_ < 0)
		Decide();
	
	Act();
}

void AI_Entity::Update_Timer(float& cooldown, float& interval)
{
	if (cooldown < 0)
	{
		cooldown = interval;
	}

	cooldown -= Time::Get_Delta_Time().As_Seconds();
}



void AI_Entity::Render()
{
	SDL_SetRenderDrawColor(renderer_, colour_.r, colour_.g, colour_.b, colour_.a);
	SDL_Rect rect = SDL_Rect({ (int) x_, (int) y_, 90, 90 }); SDL_RenderFillRect(renderer_, &rect);
	SDL_SetRenderDrawColor(renderer_, colour_.r, colour_.g, colour_.b, colour_.a);
}

void AI_Entity::Destroy()
{

}

void AI_Entity::Set_Colour(int r, int g, int b, int a)
{
	colour_ = SDL_Color{ (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a };
}
