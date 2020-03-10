// Sheep.h

#ifndef __SHEEP__
#define __SHEEP__

#include "Agent.h"

struct Sheep : Agent
{
	Sheep();
	~Sheep();

	// Loop
	virtual void Update() override;
	virtual void Render() override;

	// AI
	virtual void Sense() override;
	virtual void Decide() override;
	virtual void Act() override;
};

#endif // !__GRASS__
