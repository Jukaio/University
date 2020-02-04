#include "AI_Entity.h"

AI_Entity::AI_Entity()
	: x_(0)
	, y_(0)
	, current_State_(IDLE)
{

}

void AI_Entity::Create(Grid* grid_, SDL_Renderer* renderer, int x, int y)
{
	x_ = (float) x;
	y_ = (float) y;
	renderer_ = renderer;
	grid_ = grid_;
	current_State_ = WANDER;
}

void AI_Entity::Sense()
{

}

void AI_Entity::Decide()
{
}

void AI_Entity::Act()
{
}

void AI_Entity::Update(float dt)
{
	switch (current_State_)
	{
		case IDLE:

			break;

		case WANDER:
			x_ += dt;
			break;
	}
}

void AI_Entity::Render()
{
	SDL_Colour colour = SDL_Colour({ 255, 255, 255, 255 });

	SDL_SetRenderDrawColor(renderer_, colour.r, colour.g, colour.b, colour.a);
	SDL_Rect rect = SDL_Rect({ (int) x_, (int) y_, 90, 90 }); SDL_RenderFillRect(renderer_, &rect);
	SDL_SetRenderDrawColor(renderer_, colour.r, colour.g, colour.b, colour.a);
}
