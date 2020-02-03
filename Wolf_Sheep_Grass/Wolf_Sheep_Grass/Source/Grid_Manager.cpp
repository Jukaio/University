//Grid_Manager.cpp

#include "Grid_Manager.h"

Grid_Manager::Grid_Manager()
	: size_(0)
	, grids_(nullptr)
	, tile_Size_(0)
{

}

void Grid_Manager::Create(SDL_Renderer* renderer, int tile_Size)
{
	renderer_ = renderer;
	tile_Size_ = tile_Size;
}

void Grid_Manager::Add_Grid(int x, int y, int w, int h)
{
	Grid* temp_Grids = grids_;
	grids_ = new Grid[size_ + 1];

	Grid temp_Grid;
	temp_Grid.Create(x, y, w, h, tile_Size_, renderer_);

	for (int i = 0; i < size_; i++)
		grids_[i] = temp_Grids[i];
	grids_[size_] = temp_Grid;
	size_++;
}

void Grid_Manager::Plant_Global(int x, int y)
{
	for (int i = 0; i < size_; i++)
	{
		int temp_x = grids_[i].x_;
		int temp_y = grids_[i].y_;
		int temp_Width = grids_[i].width_;
		int temp_Height = grids_[i].height_;
		int temp_Tile_Size = grids_[i].tile_Size_;

		if (x >= temp_x &&
			x < temp_x + temp_Width / temp_Tile_Size &&
			y >= temp_y &&
			y < temp_y + temp_Height / temp_Tile_Size)
		{
			int tile_Index = (y * (temp_Width / temp_Tile_Size)) + x;
			grids_[i].tiles_[tile_Index].Set_Colour(0, 255, 0, 255);
		}
	}
}

Tile Grid_Manager::Get_Tile(int x, int y)
{
	for (int i = 0; i < size_; i++)
	{
		int temp_x = grids_[i].x_;
		int temp_y = grids_[i].y_;
		int temp_Width = grids_[i].width_;
		int temp_Height = grids_[i].height_;
		int temp_Tile_Size = grids_[i].tile_Size_;

		if (x >= temp_x &&
			x < temp_x + temp_Width / temp_Tile_Size &&
			y >= temp_y &&
			y < temp_y + temp_Height / temp_Tile_Size)
		{
			int tile_Index = (y * (temp_Width / temp_Tile_Size)) + x;
			return grids_[i].tiles_[tile_Index];
		}
	}

	return Tile();
}

void Grid_Manager::Render()
{
	for (int i = 0; i < size_; i++)
		grids_[i].Render();
}
