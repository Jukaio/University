// Game_Object.cpp

#include "Game_Object.h"
#include <SDL2/SDL.h>
#include "Keyboard.h"

void Game_Object::Update()
{

}

void Game_Object::Render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_Rect rect = { (int)position_.x_, (int)position_.y_, (int) size_.x_, (int) size_.y_ };
	SDL_RenderFillRect(renderer, &rect);
}
