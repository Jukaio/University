
#include <iostream>
#include <SDL.h>

struct Tile
{
	int x_, y_;
	int width_;
	int height_;
	SDL_Color color_;
	Tile()
		: width_(0)
		, height_(0)
		, x_(0)
		, y_(0)
	{
		color_ = SDL_Color{ 0, 0, 0, 0 };
	}

	Tile(int x, int y, int w, int h)
		: width_(w)
		, height_(h)
		, x_(x)
		, y_(y)
	{
		color_ = SDL_Color{ 255, 0, 0, 255 };
	}

	void Set_Colour(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	{
		color_ = SDL_Color{ r, g, b, a };
	}

	void Render(SDL_Renderer* renderer)
	{
		SDL_SetRenderDrawColor(renderer, color_.r, color_.g, color_.b, color_.a);
		SDL_RenderFillRect(renderer, new SDL_Rect{ x_, y_, width_, height_ });
	}
};

struct Grid
{
	Tile* tiles_;
	Grid()
	{
		tiles_ = new Tile[10 * 10];

		int index = 0;
		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				Tile tile = Tile(x * (1000 / 10), y * (1000 / 10), 1000 / 10, 1000 / 10);
				tile.Set_Colour(255, 0, 0, 255);

				tiles_[y * 10 + x] = tile;
			}
		}
	}

	void Render(SDL_Renderer* renderer)
	{
		int index = 0;
		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				int tile_Index = y * 10 + x;
				tiles_[tile_Index].Render(renderer);
			}
		}
	}
};

int main(int ac, char** av)
{
	Grid grid;

	SDL_Window* window = SDL_CreateWindow("Eco", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, 0);

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			std::cout << grid.tiles_[y * 10 + x].x_ << "x" << grid.tiles_[y * 10 + x].y_ << " ";
		}
		std::cout << "\n";
	}


	bool running = true;
	while (running)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		grid.Render(renderer);

		SDL_RenderPresent(renderer);
	}

	return 0;
}