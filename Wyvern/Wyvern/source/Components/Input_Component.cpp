// Input_Component.cpp

#include "Components\Input_Component.h"
#include "Components/Transform.h"
#include "Input/Keyboard.h"
#include <SDL2/SDL_keycode.h>
#include "Game_Object.h"
#include "Vector2.h"
#include "Time.h"

Input_Component::Input_Component(Game_Object& game_object)
	: Component(game_object)
{

}

void Input_Component::Update()
{
	Transform* transform = game_Object_.Get_Component<Transform>();
	
	Vector2 velocity = Vector2(0, 0);
	float speed = 300.0f;

	if (Keyboard::Key_State(SDL_SCANCODE_A))
	{
		velocity += Vector2(-1, 0);
	}
	if (Keyboard::Key_State(SDL_SCANCODE_D))
	{
		velocity += Vector2(1, 0);
	}

	if (Keyboard::Key_State(SDL_SCANCODE_W))
	{
		velocity += Vector2(0, -1);
	}
	if (Keyboard::Key_State(SDL_SCANCODE_S))
	{
		velocity += Vector2(0, 1);
	}
	velocity.Normalise();
	transform->Set_Position(transform->Get_Position() + (velocity * speed * Time::Get_Delta_Time().As_Seconds()));
}
