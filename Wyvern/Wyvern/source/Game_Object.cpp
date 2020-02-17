// Game_Object.cpp

#include "Game_Object.h"
#include <SDL2/SDL.h>
#include "Keyboard.h"

Game_Object::Game_Object()
{

}

Game_Object::Game_Object(Vector2 position, Vector2 size)
{
	position_ = position;
	size_ = size;
}

Game_Object::Game_Object(Vector2 position, float w, float h)
{
	position_ = position;
	size_ = Vector2(w, h);
}

Game_Object::Game_Object(float x, float y, Vector2 size)
{
	position_ = Vector2(x, y);
	size_ = size;
}

Game_Object::Game_Object(float x, float y, float w, float h)
{
	position_ = Vector2(x, y);
	size_ = Vector2(w, h);
}

Game_Object::Game_Object(int x, int y, int w, int h)
{
	position_ = Vector2(x, y);
	size_ = Vector2(w, h);
}



void Game_Object::Update()
{

}

void Game_Object::Render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_Rect rect = { (int)position_.x_, (int)position_.y_, (int) size_.x_, (int) size_.y_ };
	SDL_RenderFillRect(renderer, &rect);
}
