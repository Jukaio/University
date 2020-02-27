// Input_Component.h

#ifndef __INPUT_COMPONENT_
#define __INPUT_COMPONENT_

#include "Component.h"

struct Input_Component : Component
{
	Input_Component(Game_Object& game_object);
	void Update();

};


#endif // !__INPUT_COMPONENT_




