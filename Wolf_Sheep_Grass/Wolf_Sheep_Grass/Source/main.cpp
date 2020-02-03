
#include <iostream>
#include <SDL.h>
#include <chrono>

#include "Grid_Manager.h"

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 900;
const int GRID_TILE_SIZE = 90;

struct AI_Object
{
	Grid_Manager* grid_Manager_;

	float x_;
	float y_;
	float timer_;
	SDL_Renderer* renderer_;

	SDL_Colour colour_;

	AI_Object()
		: renderer_(nullptr)
		, grid_Manager_(nullptr)
		, x_(0)
		, y_(0)
		, timer_(0)
		, colour_({ 0, 0, 0, 0 })
	{

	}

	void create(SDL_Renderer* renderer, int x, int y)
	{
		renderer_ = renderer;
		colour_ = SDL_Color{ 255, 255, 255, 255 };
		x_ = x;
		y_ = y;
		timer_ = 0.5f;
	}
	void update(float dt)
	{

	}

	void render()
	{
		SDL_SetRenderDrawColor(renderer_, colour_.r, colour_.g, colour_.b, colour_.a);
		SDL_Rect rect{ (int) x_, (int) y_, 80, 80 };
		SDL_RenderFillRect(renderer_, &rect);
	}
	void destroy()
	{

	}



};

int main(int ac, char** av)
{
	SDL_Window* window = SDL_CreateWindow("Eco", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, 0);

	SDL_Event event;

	int x, y;


	AI_Object ai_Idiot;
	ai_Idiot.create(renderer, 30, 80);

	Grid_Manager grid;
	grid.Create(renderer, GRID_TILE_SIZE);
	grid.Add_Grid(0, 0, 900, 900);

	for (int i = 0; i < 20; i++)
		grid.Plant_Global(i, i);

	auto tp = std::chrono::steady_clock::now();

	bool running = true;
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				running = false;
		}

		//Get DeltaTime
		float dt;
		{
			const auto new_tp = std::chrono::steady_clock::now();
			dt = std::chrono::duration<float>(new_tp - tp).count();
			tp = new_tp;
		}
		Uint32 coordinates = SDL_GetMouseState(&x, &y);
		Tile tile = grid.Get_Tile(x / GRID_TILE_SIZE, y / GRID_TILE_SIZE);
		std::cout << "x: " << x << " | y: " << y << " || " << "Tile x: " << tile.x_ << " | y: " << tile.y_ << " || " << "Tile Index x: " << tile.x_ / GRID_TILE_SIZE << " | y: " << tile.y_ / GRID_TILE_SIZE << "\n";
		

		/*SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);*/
		ai_Idiot.update(dt);

		grid.Render();
		ai_Idiot.render();

		SDL_RenderPresent(renderer);
	}

	return 0;
}