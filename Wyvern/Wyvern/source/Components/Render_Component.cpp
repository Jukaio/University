// Render.cpp

#include "Components/Render_Component.h"
#include "Renderer.h"
#include <SDL2/SDL.h>
#include "Components/Transform_Component.h"
#include "Game_Object.h"
#include "Vector2.h"
#include "Texture_Manager.h"

Render_Component::Render_Component(Game_Object& game_object)
	: Component(game_object)
{
}

void Render_Component::Render_Square()
{
	Transform_Component* transform = game_Object_.Get_Component<Transform_Component>();

	SDL_SetRenderDrawColor(Renderer::Get_Renderer(), 255, 0, 0, 255);
	SDL_Rect rect = { (int)transform->Get_Position().x_, (int)transform->Get_Position().y_, (int)transform->Get_Size().x_, (int)transform->Get_Size().y_ };
	SDL_RenderFillRect(Renderer::Get_Renderer(), &rect);
}

void Render_Component::Render_Frame(std::string id)
{
	Transform_Component* transform = game_Object_.Get_Component<Transform_Component>();
	SDL_Texture* texture = Texture_Manager::Get(id);
	
	// Add things for the dest Rect to change the destination size
	SDL_Rect srcRect = SDL_Rect({ 0, 0, (int) transform->Get_Size().x_, (int) transform->Get_Size().y_ });
	SDL_Rect destRect = SDL_Rect({ (int)transform->Get_Position().x_, (int)transform->Get_Position().y_,
								(int)transform->Get_Size().x_, (int)transform->Get_Size().y_ });

	SDL_RenderCopyEx(Renderer::Get_Renderer(), texture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

