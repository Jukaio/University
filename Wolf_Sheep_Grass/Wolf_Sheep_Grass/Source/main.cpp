
#include <iostream>
#include <SDL.h>
#include <chrono>

#include "Grid_Manager.h"

int SCREEN_WIDTH = 900;
int SCREEN_HEIGHT = 900;
int GRID_TILE_SIZE = 10;

//struct Tile
//{
//	int x_, y_;
//	int width_;
//	int height_;
//	SDL_Color color_;
//	Tile()
//		: width_(0)
//		, height_(0)
//		, x_(0)
//		, y_(0)
//	{
//		color_ = SDL_Color{ 0, 0, 0, 0 };
//	}
//
//	Tile(int x, int y, int w, int h)
//		: width_(w)
//		, height_(h)
//		, x_(x)
//		, y_(y)
//	{
//		color_ = SDL_Color{ 255, 0, 0, 255 };
//	}
//
//	void Set_Colour(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
//	{
//		color_ = SDL_Color{ r, g, b, a };
//	}
//
//	void Render(SDL_Renderer* renderer)
//	{
//		SDL_SetRenderDrawColor(renderer, color_.r, color_.g, color_.b, color_.a);
//		SDL_RenderFillRect(renderer, new SDL_Rect{ x_, y_, width_, height_ });
//	}
//};
//
//struct Grid //Child Grid
//{
//	int x_;
//	int y_;
//	int width_;
//	int height_;
//
//	Tile* tiles_;
//	unsigned int size_;
//
//	Grid()
//		: tiles_(nullptr)
//		, x_(NULL)
//		, y_(NULL)
//		, width_(NULL)
//		, height_(NULL)
//		, size_(0)
//	{
//
//	}
//
//	Grid(int x, int y, int w, int h)
//		: x_(x)
//		, y_(y)
//		, width_(w)
//		, height_(h)
//		, size_(0)
//	{
//		tiles_ = new Tile[width_ / GRID_TILE_SIZE * height_ / GRID_TILE_SIZE];
//
//		int index = 0;
//		int red = 30;
//		for (int y = 0; y < height_ / GRID_TILE_SIZE; y++)
//		{
//			for (int x = 0; x < width_ / GRID_TILE_SIZE; x++)
//			{
//				Tile tile = Tile(x_ + (x * GRID_TILE_SIZE), y_ + (y * GRID_TILE_SIZE), GRID_TILE_SIZE, GRID_TILE_SIZE);
//				tile.Set_Colour(red, 0, 0, 255);
//
//				int tile_Index = y * (width_ / GRID_TILE_SIZE) + x;
//				tiles_[tile_Index] = tile;
//				red += 15;
//				if (red > 255)
//					red = 30;
//				size_++;
//			}
//		}
//	}
//
//	void Render(SDL_Renderer* renderer)
//	{
//		int index = 0;
//		for (int y = 0; y < height_ / GRID_TILE_SIZE; y++)
//		{
//			for (int x = 0; x < width_ / GRID_TILE_SIZE; x++)
//			{
//				int tile_Index = y * (width_/GRID_TILE_SIZE) + x;
//				tiles_[tile_Index].Render(renderer);
//			}
//		}
//	}
//};
//
//struct Grid_Manager //Parent Grid
//{
//	Grid* grids_;
//	int size_;
//	SDL_Renderer* renderer_;
//
//	Grid_Manager()
//		: grids_(nullptr)
//		, size_(0)
//		, renderer_(nullptr)
//	{
//
//	}
//
//	void Create(SDL_Renderer* renderer)
//	{
//		renderer_ = renderer;
//	}
//
//	void Add_Grid(int x, int y, int w, int h)
//	{
//		Grid* temp = grids_;
//		grids_ = new Grid[size_ + 1];
//
//		for(int i = 0; i < size_; i++)
//		{
//			grids_[i] = temp[i];
//		}
//		grids_[size_] = Grid(x, y, w, h);
//
//		size_++;
//	}
//
//	void Fill_Screen_With_Grid()
//	{
//		int width = SCREEN_WIDTH / 2;
//		int height = SCREEN_HEIGHT / 2;
//
//		this->Add_Grid(0, 0, width, height);
//		this->Add_Grid(width, 0, width, height);
//		this->Add_Grid(0, height, width, height);
//		this->Add_Grid(width, height, width, height);
//	}
//
//	void Plant_Local(int x, int y, int grid_Index)
//	{
//		int green = 125;
//
//		int tile_Index = y * (grids_[grid_Index].width_ / GRID_TILE_SIZE) + x;
//		Grid grid_Test = grids_[grid_Index];
//		grid_Test;
//		grids_[grid_Index].tiles_[tile_Index].Set_Colour(0, green, 0, 255);
//	}
//
//	void Plant_Global(int x, int y)
//	{
//		for (int i = 0; i < size_; i++)
//		{
//			int grid_x = grids_[i].x_;
//			int grid_Width = grids_[i].width_;
//			int grid_y = grids_[i].y_;
//			int grid_Height = grids_[i].height_;
//
//
//
//			if (x >= grid_x ||
//				x <= grid_Width + grid_x ||
//				y >= grid_y ||
//				y <= grid_Height + grid_y)
//			{
//				int tile_Index = (y - grid_y) * (grid_Width / GRID_TILE_SIZE) + (x - grid_x);
//				Tile temp_Tile = grids_[i].tiles_[tile_Index];
//				temp_Tile.Set_Colour(0, 0, 255, 255);
//				return;
//			}
//
//			std::cout << "Position out of range \n";
//
//
//		}
//	}
//
//	void Expand(int x, int y, int grid_Index)
//	{
//
//		int tile_Index = y * (grids_[grid_Index].width_ / GRID_TILE_SIZE) + x;
//		Tile temp = grids_[grid_Index].tiles_[tile_Index];
//		if (temp.color_.g == 125)
//		{
//			int radius_Tiles[4] =
//			{
//				tile_Index - 1,
//				tile_Index + 1,
//				tile_Index - grids_[grid_Index].width_ / GRID_TILE_SIZE,
//				tile_Index + grids_[grid_Index].width_ / GRID_TILE_SIZE,
//			};
//
//			for (int i = 0; i < 4; i++)
//			{
//				grids_[grid_Index].tiles_[radius_Tiles[i]].Set_Colour(0, 125, 0, 255);
//			}
//			grids_[grid_Index].tiles_[tile_Index].Set_Colour(0, 175, 0, 255);
//		}
//	}
//
//	void Render()
//	{
//		for (int i = 0; i < size_; i++)
//			grids_[i].Render(renderer_);
//	}
//
//};
//
int main(int ac, char** av)
{
	SDL_Window* window = SDL_CreateWindow("Eco", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, 0);

	//Grid_Manager grid;
	//grid.Create(renderer);
	//grid.Fill_Screen_With_Grid();

	////grid.Add_Grid(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	//grid.Plant_Local(2, 2, 0);
	//grid.grids_[0].size_;
	//grid.Plant_Local(100, 90, 0);
	////grid.Plant(4, 0, 2);
	////grid.Plant(1, 3, 3);

	////grid.Expand(12, 20, 0);

	////grid.Plant_Global(900, 900);
	////grid.Expand(2, 2, 2);

	Grid_Manager grid;
	grid.Create(renderer, 1);
	grid.Add_Grid(500, 500, 200, 200);
	grid.Add_Grid(0, 0, 400, 400);

	for (int i = 0; i < 20; i++)
		grid.Plant_Global(i, i);

	auto tp = std::chrono::steady_clock::now();

	bool running = true;
	while (running)
	{
		//Get DeltaTime
		float dt;
		{
			const auto new_tp = std::chrono::steady_clock::now();
			dt = std::chrono::duration<float>(new_tp - tp).count();
			tp = new_tp;
		}

		/*SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);*/


		grid.Render();

		SDL_RenderPresent(renderer);
	}

	return 0;
}