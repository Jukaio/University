//Tile.cpp

#include "Tile.h"

Tile::Tile()
	: x_(0)
	, y_(0)
	, width_(0)
	, height_(0)
	, colour_({ 0, 0, 0, 0 })
	, grass_Level_(0)
{

}

void Tile::Create(int x, int y, int w, int h, 
				  int r, int g, int b, int a)
{
	x_ = x;
	y_ = y;
	width_ = w;
	height_ = h;
	colour_ = SDL_Color{ (Uint8) r, (Uint8) g, (Uint8) b, (Uint8) a };
}

void Tile::Set_Colour(int r, int g, int b, int a)
{
	colour_ = SDL_Color{ (Uint8) r, (Uint8) g, (Uint8)b, (Uint8) a };
}

void Tile::Render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, colour_.r, colour_.g, colour_.b, colour_.a);
	SDL_Rect rect { x_, y_, width_, height_ };
	SDL_RenderFillRect(renderer, &rect);
}