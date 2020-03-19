#include "Time.h"

Time::Time()
{
	tp_ = SDL_GetTicks();
}

void Time::Update()
{
	Ticks dt;
	{
		const Ticks new_Tp = SDL_GetTicks();
		dt = new_Tp.tick_Rate_ - tp_.tick_Rate_;
		tp_ = new_Tp;
	}
	dt_ = dt;
}


Time::~Time()
{

}

Ticks Time::Delta_Time()
{
	return dt_;
}

Ticks Time::Run_Time()
{
	Ticks total = SDL_GetTicks();
	return total;
}


