//Keyboard.cpp

#include "Input/Keyboard.h"
#include <iostream>

Keyboard::Keyboard()
{
}

Keyboard* Keyboard::instance_ = nullptr;

void Keyboard::Initialise()
{
	if (instance_ == nullptr)
		instance_ = new Keyboard();
	else
		std::cout << "Double Initialisation of Keyboard [Keyboard.cpp | Keyboard::Initialisation]\n";
}

void Keyboard::Update()
{
	for (int i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		instance_->last_Frame_[i] = instance_->current_Frame_[i];
	}
}

void Keyboard::Update_Key(SDL_Scancode key, bool value)
{
	instance_->current_Frame_[key] = value;
}

bool Keyboard::Key_State(SDL_Scancode key)
{
	return instance_->current_Frame_[key];
}

bool Keyboard::Key_Pressed(SDL_Scancode key)
{
	return (instance_->last_Frame_[key] == false && instance_->current_Frame_[key] == true);
}

bool Keyboard::Key_Released(SDL_Scancode key)
{
	return (instance_->last_Frame_[key] == true && instance_->current_Frame_[key] == false);
}

