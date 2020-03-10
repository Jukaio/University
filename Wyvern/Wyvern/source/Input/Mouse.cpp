// Mouse.cpp

#include "Input\Mouse.h"
#include <iostream>

Mouse::Mouse()
	: position_(0, 0) { }

Mouse::~Mouse()
{
}

void Mouse::Set_Mouse_Position(int& x, int& y)
{
	position_ = Vector2(x, y);
}

Vector2 Mouse::Get_Mouse_Position()
{
	return position_;
}

