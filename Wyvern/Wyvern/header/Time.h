//Time.h

#ifndef __Time__
#define __Time__

#include <SDL2/SDL.h>

struct Ticks
{
	Uint32 tick_Rate_;

	float As_Seconds()
	{
		return tick_Rate_ / 1000.0f;
	}

	int As_Miliseconds()
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
	static void Initialise();
	static void Update();
	static void Clean();


	static Ticks Get_Delta_Time();

private:
	static Time* instance_;
	Time();
	~Time();
	Ticks tp_;
	Ticks dt_;
};


#endif // !__Time__



