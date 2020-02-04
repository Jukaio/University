
#include <iostream>
#include <SDL.h>
#include <chrono>

#include "Grid.h"
#include "AI_Entity.h"

int main(int ac, char** av)
{
	SDL_Window* window = SDL_CreateWindow("Eco", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, 0);

	SDL_Event event;

	Grid grid;
	grid.Create(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, TILE_SIZE, renderer);
	
	AI_Entity ai;
	ai.Create(&grid, renderer, 90, 90);


	int x, y;

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
		
		grid.Render();
		ai.Update(dt);
		ai.Render();

		Uint32 coordinates = SDL_GetMouseState(&x, &y);
		std::cout << "x: " << x << " | y: " << y << " || " << " Tile x: " << grid.Get_Tile(x,y).x_ << " y: " << grid.Get_Tile(x, y).y_ << "\n";
		

		SDL_RenderPresent(renderer);
	}

	return 0;
}