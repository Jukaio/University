//Grid.cpp

#ifndef __GRID__
#define __GRID__

#include "Tile.h"

struct Grid
{
	int x_, y_;
	int width_, height_;
	int tile_Size_; //width and height of tile

	Tile* tiles_;

	unsigned int size_;
	
	SDL_Renderer* renderer_;

	Grid();

	void Create(int x, int y, int w, int h, unsigned int tile_Size, SDL_Renderer* renderer);
	void Render();
};


#endif // !__GRID__
