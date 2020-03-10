// Texture_Manager.cpp

#include "Engine/Texture_Manager.h"
#include <SDL_image/SDL_image.h>
#include "Service.h"
#include "Engine/SDL_Pipeline.h"
#include <iostream>
#include <SDL2/SDL.h>

Texture_Manager::Texture_Manager()
{

}

Texture_Manager::~Texture_Manager()
{

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

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Service<SDL_Pipeline>::Get()->Get_Renderer(), surface);
	text->texture_ = texture;
	text->src_Rect_ = SDL_Rect({ 0, 0, surface->w, surface->h });

	SDL_FreeSurface(surface);

	if (texture == nullptr)
	{
		std::cout << "Img on disk not found! \n";
		return false;
	}
	texture_Cache_.Add(id, text);
	std::cout << "Img in " << path << " loaded \n";
	return true;
}

Texture_Data* Texture_Manager::Get(std::string id)
{
	Texture_Data* texture = texture_Cache_.Get(id);
	if (texture == nullptr)
		std::cout << "Img in cache not found! \n";
	return texture;
}

