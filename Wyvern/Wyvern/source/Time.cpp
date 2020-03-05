#include "Time.h"

Time::Time()
{
	tp_ = SDL_GetTicks();
}

void Time::Update()
{
	Ticks dt;
	{
		Ticks new_Tp = SDL_GetTicks();
		dt = new_Tp.tick_Rate_ - tp_.tick_Rate_;
		tp_ = new_Tp;
	}
	dt_ = dt;
}


Time::~Time()
{

}

Ticks Time::Get_Delta_Time()
{
	return dt_;
}


