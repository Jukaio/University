// Render.h

#ifndef __RENDER_COMPONENT__
#define __RENDER_COMPONENT__

#include "Component.h"
#include <string>

struct Render_Component : Component
{
	Render_Component(Game_Object& game_object);
	void Render_Square();
	void Render_Frame(std::string id);
};


#endif // !__RENDER_COMPONENT__




