//Keyboard.cpp

#include "Input/Keyboard.h"
#include <iostream>

Keyboard::Keyboard() 
{

}

Keyboard::~Keyboard()
{
}


void Keyboard::Update_Last_Frame()
{
	for (int i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		last_Frame_[i] = current_Frame_[i];
	}
}

void Keyboard::Update_Key(SDL_Scancode key, bool value)
{
	current_Frame_[key] = value;
}

bool Keyboard::Key_State(SDL_Scancode key)
{
	return current_Frame_[key];
}

bool Keyboard::Key_Pressed(SDL_Scancode key)
{
	return (last_Frame_[key] == false && current_Frame_[key] == true);
}

bool Keyboard::Key_Released(SDL_Scancode key)
{
	return (last_Frame_[key] == true && current_Frame_[key] == false);
}

