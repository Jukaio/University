// Wolf.h

#ifndef __WOLF__
#define __WOLF__

#include "Agent.h"

struct Wolf : Agent
{
	Wolf();
	~Wolf();

	// Loop
	virtual void Update() override;
	virtual void Render() override;

	// AI
	virtual void Sense() override;
	virtual void Decide() override;
	virtual void Act() override;
};

#endif // !__WOLF__
