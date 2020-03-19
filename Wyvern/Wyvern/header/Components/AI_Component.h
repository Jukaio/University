// AI_Component.h

#ifndef __AI_COMPONENT__
#define __AI_COMPONENT__

#include "Component.h"
#include "Service.h"
#include "Time.h"
#include <iostream>

struct Game_Object;

struct AI_Component : Component
{
	AI_Component(Game_Object* game_object, float sense_rate, float decide_rate, float act_rate)
		: Component(game_object)
		, sense_Rate_(sense_rate)
		, sense_(sense_rate)
		, decide_Rate_(decide_rate)
		, decide_(decide_rate)
		, act_Rate_(act_rate)
		, act_(act_rate)
	{

	}
	virtual ~AI_Component() = default;

	void Update()
	{
		if (Cooldown(sense_, sense_Rate_))
			Sense();

		if (Cooldown(decide_, decide_Rate_))
			Decide();

		if (Cooldown(act_, act_Rate_))
			Act();
	}

	static bool Cooldown(float& time, const float rate)
	{
		time -= Service<Time>::Get()->Delta_Time().As_Seconds();
		if (time <= 0)
		{
			time = rate;
			return true;
		}
		return false;
	}

private:
	float sense_Rate_;
	float decide_Rate_;
	float act_Rate_;

	float sense_;
	float decide_;
	float act_;

	virtual void Sense() = 0;
	virtual void Decide() = 0;
	virtual void Act() = 0;

};

#endif // !__AI_COMPONENT__
