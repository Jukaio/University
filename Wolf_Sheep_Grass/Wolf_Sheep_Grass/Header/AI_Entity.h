//AI_Entity.h

#ifndef __AI_ENTITY__
#define __AI_ENTITY__

#include <SDL.h>
#include <Grid.h>

struct AI_Entity
{
	enum State
	{
		IDLE,
		WANDER
	};

	State current_State_;
	float x_, y_;

	Grid* grid_;
	SDL_Renderer* renderer_;

	AI_Entity();
	void Create(Grid* grid_, SDL_Renderer* renderer, int x, int y);

	void Sense();
	void Decide();
	void Act();

	void Update(float dt);
	void Render();

};

#endif // !__AI_ENTITY__



