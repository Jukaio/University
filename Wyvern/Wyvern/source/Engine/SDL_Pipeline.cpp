// SDL_Pipeline.cpp

#include "Engine/SDL_Pipeline.h"
#include <SDL2/SDL.h>
#include <SDL_image/SDL_image.h>
#include <SDL_Font/SDL_ttf.h>

SDL_Pipeline::SDL_Pipeline()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL Initialisation: Failure %s", SDL_GetError());

	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Image Initialisation: Failure %s", IMG_GetError());

	if (TTF_Init() != 0)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Font Initialisation: Failure %s", TTF_GetError());

	window_ = SDL_CreateWindow("Wyvern", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	if(window_ == nullptr)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window Initialisation: Failure %s", SDL_GetError());
	
	renderer_ = SDL_CreateRenderer(window_, -1, 0);
	if(renderer_ == nullptr)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer Initialisation: Failure %s", SDL_GetError());
}

SDL_Pipeline::~SDL_Pipeline()
{
	if (renderer_ != nullptr)
		SDL_DestroyRenderer(renderer_);

	if (window_ != nullptr)
		SDL_DestroyWindow(window_);

	renderer_ = nullptr;
	window_ = nullptr;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

SDL_Renderer* SDL_Pipeline::Get_Renderer()
{
	return renderer_;
}

SDL_Window* SDL_Pipeline::Get_Window()
{
	return window_;
}
