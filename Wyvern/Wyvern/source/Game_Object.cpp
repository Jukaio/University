// Game_Object.cpp

#include "Game_Object.h"
#include <SDL2/SDL.h>
#include "Keyboard.h"
#include "Time.h"
#include "Renderer.h"
#include "Collision_Detection/Collider.h"

Game_Object::Game_Object()
	:collider_(Rectangle(Vector2(0, 0), Vector2(0, 0)))
	, parent_(nullptr)
{

}

Game_Object::Game_Object(Vector2 position, Vector2 size, Vector2 origin, Game_Object* parent) 
	: parent_(parent)
{
	position_ = position;
	size_ = size;
	origin_ = origin;
	collider_ = Rectangle((*this));
}




void Game_Object::Update()
{

}

void Game_Object::Render()
{
	SDL_SetRenderDrawColor(Renderer::Get_Renderer(), 255, 0, 0, 255);
	SDL_Rect rect = { (int)position_.x_ - (origin_.x_ * size_.x_), (int)position_.y_ - (origin_.y_ * size_.y_), (int) size_.x_, (int) size_.y_ };
	SDL_RenderFillRect(Renderer::Get_Renderer(), &rect);
}

void Game_Object::Set_Origin(Vector2 origin)
{
	origin_ = origin;
}

void Game_Object::Set_Origin(int x, int y)
{
	origin_ = Vector2(x, y);
}

void Game_Object::Set_Origin(float x, float y)
{
	origin_ = Vector2(x, y);
}
