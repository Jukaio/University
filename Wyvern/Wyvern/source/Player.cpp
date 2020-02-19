// Player.h

#include "Player.h"
#include "Time.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <SDL2/SDL_scancode.h>
#include "World.h"
#include "Collision_Detection/Collision.h"
#include <iostream>
#include "Renderer.h"


Player::Player() { }

Player::Player(Vector2 position, Vector2 size, Vector2 origin, World* parent)
	: Game_Object(position, size, origin)
	, world_(parent) 
{
	green_ = 0;
}



void Player::Update()
{
	Vector2 velocity = Vector2(0, 0);

	if (Keyboard::Key_State(SDL_SCANCODE_UP) && !Keyboard::Key_State(SDL_SCANCODE_DOWN))
		velocity += Vector2(0, -1);
	else if (Keyboard::Key_State(SDL_SCANCODE_DOWN) && !Keyboard::Key_State(SDL_SCANCODE_UP))
		velocity += Vector2(0, 1);

	if (Keyboard::Key_State(SDL_SCANCODE_LEFT) && !Keyboard::Key_State(SDL_SCANCODE_RIGHT))
		velocity += Vector2(-1, 0);
	else if (Keyboard::Key_State(SDL_SCANCODE_RIGHT) && !Keyboard::Key_State(SDL_SCANCODE_LEFT))
		velocity += Vector2(1, 0);
	velocity.Normalise();

	position_ += velocity * Time::Get_Delta_Time().As_Seconds() * 500;

	collider_.Update_Position(position_);

	green_ = 0;
	if (Collision(collider_, world_->Get_Game_Objects()[0]->collider_))
		green_ = 255;
}

void Player::Render()
{
	SDL_SetRenderDrawColor(Renderer::Get_Renderer(), 255, green_, 0, 255);
	SDL_Rect rect = { (int)position_.x_ - (origin_.x_ * size_.x_), (int)position_.y_ - (origin_.y_ * size_.y_), (int)size_.x_, (int)size_.y_ };
	SDL_RenderFillRect(Renderer::Get_Renderer(), &rect);
}
