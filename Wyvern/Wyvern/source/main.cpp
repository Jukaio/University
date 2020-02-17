//main.cpp

#include <SDL2/SDL.h>
#include <iostream>
#include "Input/Input_Handler.h"
#include "Wyvern_Engine.h"
#include <SDL_Font/SDL_ttf.h>
#include <string>
#include "Game_Object.h"
#include "Time.h"
#include "Wyvern_Array.h"

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

	Vector2 vector(2, 2);
	Vector2 vector2(3, 3.0f);
	vector += vector2;

	Input_Handler input_Handler;
	input_Handler.Initialise();
	Time::Instance();
	TTF_Init();
	
	Game_Object gm;
	gm.Create(0, 300, 20, 20);

	Wyvern_Array<Game_Object> arr;
	arr.Push_Back();


	bool running = true;
	while (running)
	{
		Time::Update();

		if (!input_Handler.Handle_Input_Events())
			running = false;

		SDL_RenderClear(renderer);

		for (int i = 0; i < SDL_NUM_SCANCODES; i++)
		{
			if (Keyboard::Key_State((SDL_Scancode)i))
				Write_Text(renderer, i);
		}

		gm.Update();
		gm.Render(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderPresent(renderer);
	}

	TTF_Quit();
	SDL_Quit();

	return 0;
}
