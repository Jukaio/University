//Grid.cpp

#include "Grid.h"


Tile* Grid::Get_Tile(int x, int y)
{
	float x_Temp = (float) x / Grid::tile_Size_;
	float y_Temp = (float) y / Grid::tile_Size_;

	int x_Index = (int) x_Temp;
	int y_Index = (int) y_Temp;

	Tile* temp = &tiles_[(y_Index * (Grid::width_ / Grid::tile_Size_) + x_Index)];
	return temp;
}



Grid::Grid()
	: x_(0)
	, y_(0)
	, renderer_(nullptr)
{
	
}

//Scale the "Real size" (Aka 900 x 900) down to the tile measurement. Pos(1, 1) = Pixel(10, 10) when
// Tile_Size = 10;
void Grid::Create(const int x, const int y, SDL_Renderer* renderer)
{
	x_ = x;
	y_ = y;

	renderer_ = renderer;

	int red = 50;
	for (int vertical = 0; vertical < height_ / Grid::tile_Size_; vertical++) // y
	{
		for (int horizontal = 0; horizontal < width_ / Grid::tile_Size_; horizontal++) // x 
		{
			Tile temp_Tile;
			int tile_Index = (vertical * (width_/ Grid::tile_Size_)) + horizontal;
			int tile_x = (horizontal * Grid::tile_Size_) + x_;
			int tile_y = (vertical * Grid::tile_Size_) + y_;
			
			temp_Tile.Create(tile_x, tile_y, Grid::tile_Size_, Grid::tile_Size_, red, 0, 0, 255);
			tiles_[tile_Index] = temp_Tile;
			red += 50;

			if (red > 250)
				red = 50;
		}
	}
}

void Grid::Render()
{
	for (int vertical = 0; vertical < height_ / Grid::tile_Size_; vertical++) // y
	{
		for (int horizontal = 0; horizontal < width_ / Grid::tile_Size_; horizontal++) // x 
		{
			int tile_Index = (vertical * (width_ / Grid::tile_Size_)) + horizontal;
			tiles_[tile_Index].Render(renderer_);
		}
	}
}
