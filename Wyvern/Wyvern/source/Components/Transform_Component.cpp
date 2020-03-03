// Transform.cpp

#include "Components/Transform_Component.h"

Transform_Component::Transform_Component(Game_Object& game_object)
	: Component(game_object)
	, x_(0)
	, y_(0)
	, w_(0)
	, h_(0)
	, ori_x_(0)
	, ori_y_(0)
{

}

Transform_Component::~Transform_Component()
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

Vector2 Transform_Component::Get_Origin()
{
	return Vector2(ori_x_, ori_y_);
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

void Transform_Component::Set_Origin(Vector2 origin)
{
	ori_x_ = origin.x_;
	ori_y_ = origin.y_;
}
