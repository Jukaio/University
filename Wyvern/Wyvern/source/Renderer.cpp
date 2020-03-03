// Renderer.cpp

#include "Renderer.h"
#include <mutex>
#include <SDL2/SDL.h>

SDL_Renderer* Renderer::renderer_ = nullptr;
SDL_Window* Renderer::window_ = nullptr;

bool Renderer::initialised_ = false;

void Renderer::Initialise()
{
	if (!initialised_)
	{
		window_ = SDL_CreateWindow("Wyvern", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
		renderer_ = SDL_CreateRenderer(window_, 0, 0);
		initialised_ = true;
	}
}

SDL_Renderer* Renderer::Get_Renderer()
{
	return renderer_;
}

SDL_Window* Renderer::Get_Window()
{
	return window_;
}

void Renderer::Destroy()
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);

	renderer_ = nullptr;
	window_ = nullptr;
}
