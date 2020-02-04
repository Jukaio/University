//Grid.cpp

#ifndef __GRID__
#define __GRID__

#include "Tile.h"

const int TILE_SIZE = 90;
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 900;
const int ARRAY_SIZE = (SCREEN_WIDTH / TILE_SIZE) * (SCREEN_HEIGHT / TILE_SIZE);

struct Grid
{
	int x_, y_;
	int width_, height_;
	int tile_Size_; //width and height of tile

	Tile tiles_[ARRAY_SIZE];
	Tile Get_Tile(int x, int y);

	
	SDL_Renderer* renderer_;

	Grid();

	void Create(int x, int y, int w, int h, unsigned int tile_Size, SDL_Renderer* renderer);
	void Render();
};


#endif // !__GRID__
