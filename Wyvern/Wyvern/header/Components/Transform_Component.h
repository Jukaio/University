// Transform.h

#ifndef __TRANSFORM__
#define __TRANSFORM__

#include "Component.h"
#include "Vector2.h"

struct Transform_Component : Component
{
	float x_, y_;
	float w_, h_;

	Transform_Component(Game_Object& game_object);
	Vector2 Get_Position();
	Vector2 Get_Size();

	void Set_Position(Vector2 position);
	void Set_Size(Vector2 size);
};

#endif // !__TRANSFORM__


#include "Components/Component.h"



