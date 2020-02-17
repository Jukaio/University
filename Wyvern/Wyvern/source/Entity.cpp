// Entity.cpp

#include "Entity.h"

void Entity::Create()
{

}

void Entity::Create(Vector2 position, Vector2 size)
{
	position_ = position;
	size_ = size;
}

void Entity::Create(Vector2 position, float w, float h)
{
	position_ = position;
	size_ = Vector2(w, h);
}

void Entity::Create(float x, float y, Vector2 size)
{
	position_ = Vector2(x, y);
	size_ = size;
}

void Entity::Create(float x, float y, float w, float h)
{
	position_ = Vector2(x, y);
	size_ = Vector2(w, h);
}

void Entity::Create(int x, int y, int w, int h)
{
	position_ = Vector2(x, y);
	size_ = Vector2(w, h);
}

