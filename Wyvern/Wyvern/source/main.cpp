//main.cpp

#include <SDL2/SDL.h>
#include <iostream>
#include "Input/Input_Handler.h"
#include "Wyvern_Engine.h"
#include <SDL_Font/SDL_ttf.h>
#include <string>
#include "Vector2.h"


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
	

	TTF_Init();
	


	bool escape = false;

	bool running = true;
	while (running)
	{
		if (!input_Handler.Handle_Input_Events())
			running = false;
		


 		if (escape)
			running = false;

		//std::cout << Wyvern_Engine<Input_Handler>::Instance()->Get_Key_State(SDL_SCANCODE_SPACE) << "\n";

		SDL_RenderClear(renderer);

		for (int i = 0; i < SDL_NUM_SCANCODES; i++)
		{
			if (Keyboard::Key_State((SDL_Scancode)i))
				Write_Text(renderer, i);
		}

		// Proto-Render
		//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		//SDL_Rect rect = { (int) x, (int) y, 20, 20 };
		//SDL_RenderFillRect(renderer, &rect);


		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderPresent(renderer);
	}

	TTF_Quit();
	SDL_Quit();

	return 0;
}
