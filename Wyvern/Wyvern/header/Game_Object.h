// Game_Object.h

#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include "Entity.h"

struct Game_Object : Entity
{
	virtual void Update();
	virtual void Render(SDL_Renderer* renderer);
	
};


#endif // !__GAME_OBJECT__
