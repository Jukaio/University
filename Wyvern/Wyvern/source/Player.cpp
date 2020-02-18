// Player.h

#include "Player.h"
#include "Time.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <SDL2/SDL_scancode.h>

Player::Player() { }

Player::Player(Vector2 position, Vector2 size) 
	: Game_Object(position, size) { }

Player::Player(Vector2 position, float w, float h) 
	: Game_Object(position, w, h) { }

Player::Player(float x, float y, Vector2 size)
	:Game_Object(x, y, size) { }

Player::Player(float x, float y, float w, float h)
	: Game_Object(x, y, w, h) { }

Player::Player(int x, int y, int w, int h)
	: Game_Object(x, y, w, h) { }

void Player::Update()
{
	position_ = Mouse::Get_Mouse_Position();
}
