// Mouse.cpp

#include "Input\Mouse.h"
#include <iostream>

Mouse::Mouse()
	: position_(0, 0) { }

Mouse* Mouse::instance_ = nullptr;

void Mouse::Initialise()
{
	if (instance_ == nullptr)
		instance_ = new Mouse();
	else
		std::cout << "Double Initialisation of Mouse [Mouse.cpp | Mouse::Initialisation]\n";
}

void Mouse::Set_Mouse_Position(int& x, int& y)
{
	instance_->position_ = Vector2(x, y);
}

Vector2 Mouse::Get_Mouse_Position()
{
	return instance_->position_;
}

void Mouse::Clean()
{
	if (instance_ != nullptr)
		delete instance_;
}

