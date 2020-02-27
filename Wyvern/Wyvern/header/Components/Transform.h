// Transform.h

#ifndef __TRANSFORM__
#define __TRANSFORM__

#include "Component.h"

struct Vector2;

struct Transform : Component
{
	float x_, y_;
	float w_, h_;

	Transform(Game_Object& game_object);
	Transform() = delete;
	Vector2 Get_Position();
	Vector2 Get_Size();

	void Set_Position(Vector2 position);
	void Set_Size(Vector2 size);
};

#endif // !__TRANSFORM__


#include "Components/Component.h"



