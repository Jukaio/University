// Transform.cpp

#include "Components/Transform_Component.h"

Transform_Component::Transform_Component(Game_Object& game_object)
	: Component(game_object), x_(0), y_(0), w_(0), h_(0)
{

}

Vector2 Transform_Component::Get_Position()
{
	return Vector2(x_, y_);
}

Vector2 Transform_Component::Get_Size()
{
	return Vector2(w_, h_);
}

void Transform_Component::Set_Position(Vector2 position)
{
	x_ = position.x_;
	y_ = position.y_;
}

void Transform_Component::Set_Size(Vector2 size)
{
	w_ = size.x_;
	h_ = size.y_;
}
