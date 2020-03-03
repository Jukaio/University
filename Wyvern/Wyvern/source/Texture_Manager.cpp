// Texture_Manager.cpp

#include "Texture_Manager.h"
#include <SDL_image/SDL_image.h>
#include "Renderer.h"
#include <iostream>
#include <SDL2/SDL.h>

Texture_Manager* Texture_Manager::instance_ = nullptr;
bool Texture_Manager::initialised_ = false;

void Texture_Manager::Initialise()
{
	if (initialised_)
	{
		std::cout << "Already initialised!\n";
		return;
	}
	initialised_ = true;
	instance_ = new Texture_Manager();
}

bool Texture_Manager::Add(std::string id, std::string path)
{
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == nullptr)
	{
		std::cout << "Img on disk not found! \n";
		return false;
	}
	
	Texture_Data* text = new Texture_Data();

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer::Get_Renderer(), surface);
	text->texture_ = texture;
	text->src_Rect_ = SDL_Rect({ 0, 0, surface->w, surface->h });

	SDL_FreeSurface(surface);

	if (texture == nullptr)
	{
		std::cout << "Img on disk not found! \n";
		return false;
	}
	instance_->texture_Cache_.Add(id, text);
	std::cout << "Img in " << path << " loaded \n";
	return true;
}

Texture_Data* Texture_Manager::Get(std::string id)
{
	Texture_Data* texture = instance_->texture_Cache_.Get(id);
	if (texture == nullptr)
		std::cout << "Img in cache not found! \n";
	return texture;
}

void Texture_Manager::Destroy()
{
	delete instance_;
	instance_ = nullptr;
}

Texture_Manager::Texture_Manager()
{
	
}

Texture_Manager::~Texture_Manager()
{

}

