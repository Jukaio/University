
#include <iostream>
#include <SDL.h>

#include "World.h"
#include "Time.h"


int main(int ac, char** av)
{
	SDL_Window* window = SDL_CreateWindow("Eco", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 900, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, 0);

	SDL_Event event;

	Grid* grid = new Grid();
	grid->Create(0, 0, renderer);

	World* world = new World();
	world->Create(grid, renderer);

	Time::Instance();


	int x, y;
	bool running = true;
	while (running)
	{
		Time::Update();

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				running = false;
		}

		grid->Render();

		world->Update();
		world->Render();


		Uint32 coordinates = SDL_GetMouseState(&x, &y);

		//std::cout << "x: " << x << " | y: " << y << " || " << " Tile x: " << grid.Get_Tile(x, y)->x_ << " y: " << grid.Get_Tile(x, y)->y_ << "\n";
		
		SDL_RenderPresent(renderer);
		SDL_GetTicks();
	}

	return 0;
}