//Grid.cc

#include "Grid.h"


Tile Grid::Get_Tile(int x, int y)
{
	//x = 10
	//y = 10
	float x_Temp = (float) x / TILE_SIZE;
	float y_Temp = (float) y / TILE_SIZE;

	int x_Index = (int) x_Temp;
	int y_Index = (int) y_Temp;

	return tiles_[(y_Index * (SCREEN_WIDTH / TILE_SIZE) + x_Index)];
}

Grid::Grid()
	: x_(0)
	, y_(0)
	, width_(0)
	, height_(0)
	, renderer_(nullptr)
{

}

//Scale the "Real size" (Aka 900 x 900) down to the tile measurement. Pos(1, 1) = Pixel(10, 10) when
// Tile_Size = 10;
void Grid::Create(const int x, const int y, const int w, const int h, const unsigned int tile_Size, SDL_Renderer* renderer)
{
	x_ = x;
	y_ = y;
	width_ = w;
	height_ = h;
	tile_Size_ = tile_Size;

	renderer_ = renderer;

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
