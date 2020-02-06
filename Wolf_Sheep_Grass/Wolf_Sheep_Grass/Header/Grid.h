//Grid.cpp

#ifndef __GRID__
#define __GRID__

#include "Tile.h"

struct Grid
{
	int x_, y_;
	static const int tile_Size_ = 90;
	static const int width_ = 900, height_ = 900;
	static const int tile_Array_Size_ = (width_ / tile_Size_) * (height_ / tile_Size_);

	Tile tiles_[tile_Array_Size_];
	Tile* Get_Tile(int x, int y);

	
	SDL_Renderer* renderer_;

	Grid();

	void Create(int x, int y, SDL_Renderer* renderer);
	void Render();
};


#endif // !__GRID__
