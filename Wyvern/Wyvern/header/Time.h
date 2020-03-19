//Time.h

#ifndef __Time__
#define __Time__

#include <SDL2/SDL.h>

struct Ticks
{
	Uint32 tick_Rate_;

	float As_Seconds() const
	{
		return tick_Rate_ / 1000.0f;
	}

	int As_Miliseconds() const
	{
		return tick_Rate_;
	}

	Ticks()
	{
		tick_Rate_ = NULL;
	}

	Ticks(Uint32 rhs)
	{
		tick_Rate_ = rhs;
	}

	Ticks operator=(const Uint32 rhs)
	{
		tick_Rate_ = rhs;
		return Ticks(tick_Rate_);
	}

	Ticks operator=(const Ticks rhs)
	{
		tick_Rate_ = rhs.tick_Rate_;
		return rhs;
	}
};


struct Time
{
	Time();
	void Update();
	Ticks Delta_Time();
	Ticks Run_Time();
	~Time();

private:
	Ticks tp_;
	Ticks dt_;
};


#endif // !__Time__




