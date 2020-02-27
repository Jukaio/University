// Render.cpp

#include "Components/Render_Component.h"
#include "Renderer.h"
#include <SDL2/SDL.h>
#include "Components/Transform.h"
#include "Game_Object.h"
#include "Vector2.h"

Render_Component::Render_Component(Game_Object& game_object)
	: Component(game_object)
{
}

void Render_Component::Render_Square()
{
	Transform* transform = game_Object_.Get_Component<Transform>();

	SDL_SetRenderDrawColor(Renderer::Get_Renderer(), 255, 0, 0, 255);
	SDL_Rect rect = { (int)transform->Get_Position().x_, (int)transform->Get_Position().y_, (int)transform->Get_Size().x_, (int)transform->Get_Size().y_ };
	SDL_RenderFillRect(Renderer::Get_Renderer(), &rect);
}
