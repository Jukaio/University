//main.cpp

#include <SDL2/SDL.h>
#include <iostream>
#include "Input/Input_Handler.h"
#include "Wyvern_Engine.h"
#include <SDL_Font/SDL_ttf.h>
#include <string>
#include "Game_Object.h"
#include "Time.h"
#include "World.h"

//https://stackoverflow.com/questions/16596422/template-class-with-template-container

void Write_Text(SDL_Renderer* renderer, int i)
{
	TTF_Font* font = TTF_OpenFont("assets/font.otf", 24);
	SDL_Colour black = { 0, 0, 0, 255 };
	int w, h;
	SDL_Surface* surface = TTF_RenderText_Solid(font, std::to_string(i).c_str(), black);
	w = surface->w;
	h = surface->h;
	SDL_Rect rect2 = { i, 200, w, h };
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, NULL, &rect2);
	SDL_DestroyTexture(texture);
}

int main(int argc, char* argv[])
{
	SDL_Window* window = SDL_CreateWindow("Wyvern", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, 0);

	Input_Handler input_Handler;
	input_Handler.Initialise();
	Time::Instance();
	TTF_Init();
	
	World world;
	

	for(int i = 0; i < 10; i++)
		world.Add(Game_Object(i * 50 + 10, 200, 25, 25));

	bool running = true;
	while (running)
	{
		Time::Update();
		if (!input_Handler.Handle_Input_Events())
			running = false;

		SDL_RenderClear(renderer);

		world.Update();
		world.Render(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Time::Clean();

	TTF_Quit();
	SDL_Quit();

	return 0;
}
