// Grass.h

#ifndef __GRASS__
#define __GRASS__

#include "Agent.h"

struct Grass : Agent
{
	Grass();
	~Grass();

	// Loop
	virtual void Update() override;
	virtual void Render() override;

	// AI
	virtual void Sense() override;
	virtual void Decide() override;
	virtual void Act() override;
};

#endif // !__SHEEP__
