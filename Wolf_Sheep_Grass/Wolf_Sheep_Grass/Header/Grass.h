//Grass.h

#ifndef __Grass__
#define __Grass__

#include "AI_Entity.h"
#include <vector>

struct World;

struct Grass : public AI_Entity
{
	void Create(Grid* grid, SDL_Renderer* renderer, World* world, int x, int y, float tick_Rate_Sense, float tick_Rate_Decide);

private:
	enum class State
	{
		ROOT,
		GROW,
		EXPAND,
	};

	State current_State = State::ROOT;
	World* world_ = 0;

	float growth_ = 0;

	bool expanded = false;

	float expand_Timer_ = 2.0f;
	float expand_Interval_ = 2.0f;

	float grow_Timer_ = 0.0f;
	float grow_Interval_ = 0.02f;

	void Sense();
	void Decide();
	void Act();

	void Expand();

};

#endif // !__Grass__
