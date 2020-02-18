//main.cpp

#include <SDL2/SDL.h>
#include <iostream>
#include "Input/Input_Handler.h"
#include "Wyvern_Engine.h"
#include <SDL_Font/SDL_ttf.h>
#include <string>
#include "Player.h"
#include "Time.h"
#include "World.h"
#include "Collision_Detection/Collision.h"

// COLLISION DETECTION DONE! NOW IMPLEMENT IT! STUPID FAT UGLY CUNT :( 

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

	Rectangle rect(150, 180, 150, 200);

	Player player(100, 100, 100, 100);

	Game_Object temp(0, 200, 25, 25);
	temp.Set_Origin(0.5f, 0.5f);

	for (int i = 0; i < 10; i++)
	{
		temp.position_.x_ = i * 50;
		world.Add(Game_Object(i * 50 + 10, 200, 25, 25));
	}


	bool running = true;
	while (running)
	{
		Time::Update();
		if (!input_Handler.Handle_Input_Events())
			running = false;

		SDL_RenderClear(renderer);

		world.Update();
		player.Update();

		world.Render(renderer);
		player.Render(renderer);


		int x, y;
		SDL_GetMouseState(&x, &y);

		Rectangle rect_2(player.position_, player.size_);


		int green = 0;
		if (Collision(rect, rect_2))
			green = 255;


		SDL_SetRenderDrawColor(renderer, 255, green, 0, 255);
		SDL_Rect SDLrect = { (int)rect.position_.x_, (int)rect.position_.y_, (int)rect.size_.x_, (int)rect.size_.y_ };
		SDL_RenderFillRect(renderer, &SDLrect);

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
