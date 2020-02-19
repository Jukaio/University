#include "Time.h"

Time* Time::instance_ = 0;



void Time::Initialise()
{
	if (instance_ == 0)
	{
		instance_ = new Time();
		instance_->tp_ = SDL_GetTicks();
	}
}

Time::Time()
{
	
}

void Time::Update()
{
	Ticks dt;
	{
		Ticks new_Tp = SDL_GetTicks();
		dt = new_Tp.tick_Rate_ - instance_->tp_.tick_Rate_;
		instance_->tp_ = new_Tp;
	}
	instance_->dt_ = dt;
}

void Time::Clean()
{
	if (instance_ != nullptr)
		delete instance_;
}

Time::~Time()
{
}

Ticks Time::Get_Delta_Time()
{
	return instance_->dt_;
}


