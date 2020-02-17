// Entity.h

#ifndef __ENTITY__
#define __ENTITY__

#include "IEntity.h"

struct SDL_Renderer;

struct Entity : IEntity
{
	Entity() {};

	virtual void Update() = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;


};


#endif // !__ENTITY__