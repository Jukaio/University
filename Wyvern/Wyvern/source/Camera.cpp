// Camera.cpp

#include "Camera.h"

Camera::Camera()
	: position_(0, 0)
	, size_(0, 0)
{

}

Camera::~Camera()
{

}

void Camera::Set_Position(Vector2 position)
{
	position_ = position;
}

Vector2 Camera::Get_Position()
{
	return position_;
}

void Camera::Set_Size(Vector2 size)
{
	size_ = size;
}

Vector2 Camera::Get_Size()
{
	return size_;
}
