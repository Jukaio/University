//AI_Entity.h

#ifndef __AI_ENTITY__
#define __AI_ENTITY__

#include <SDL.h>
#include <Grid.h>

struct AI_Entity
{
	float x_, y_;
	float s_tick_Rate_, d_tick_Rate_;
	float s_Timer_, d_Timer_;

	Grid* grid_;
	SDL_Colour colour_;
	SDL_Renderer* renderer_;

	AI_Entity();
	virtual void Create(Grid* grid, SDL_Renderer* renderer, int x, int y, float tick_Rate_Sense, float tick_Rate_Decide);

	virtual void Update();
	virtual void Render();
	virtual void Destroy();

	void Set_Colour(int r, int g, int b, int a);
	static void Update_Timer(float& cooldown, float& tick_Rate);

private:
	virtual void Sense() = 0;
	virtual void Decide() = 0;
	virtual void Act() = 0;

};

#endif // !__AI_ENTITY__



