//Grid.cc

#include "Grid.h"

Grid::Grid()
	: x_(0)
	, y_(0)
	, width_(0)
	, height_(0)
	, tiles_(nullptr)
	, size_(0)
{

}

//Scale the "Real size" (Aka 900 x 900) down to the tile measurement. Pos(1, 1) = Pixel(10, 10) when
// Tile_Size = 10;
void Grid::Create(int x, int y, int w, int h, unsigned int tile_Size, SDL_Renderer* renderer)
{
	x_ = x;
	y_ = y;
	width_ = w;
	height_ = h;
	tile_Size_ = tile_Size;

	renderer_ = renderer;

	int size_ = (w / tile_Size) * (h / tile_Size);
	tiles_ = new Tile[size_];

	int red = 50;
	for (int vertical = 0; vertical < height_ / tile_Size_; vertical++) // y
	{
		for (int horizontal = 0; horizontal < width_ / tile_Size_; horizontal++) // x 
		{
			Tile temp_Tile;
			int tile_Index = (vertical * (width_/tile_Size_)) + horizontal;
			int tile_x = (horizontal * tile_Size) + x_;
			int tile_y = (vertical * tile_Size) + y_;
			
			temp_Tile.Create(tile_x, tile_y, tile_Size, tile_Size, red, 0, 0, 255);
			tiles_[tile_Index] = temp_Tile;
			red += 50;
			if (red > 250)
				red = 50;
		}
	}
}

void Grid::Render()
{
	for (int vertical = 0; vertical < height_ / tile_Size_; vertical++) // y
	{
		for (int horizontal = 0; horizontal < width_ / tile_Size_; horizontal++) // x 
		{
			int tile_Index = (vertical * (width_ / tile_Size_)) + horizontal;
			tiles_[tile_Index].Render(renderer_);
		}
	}
}
