// Agent.h

#ifndef __AGENT__
#define __AGENT__

#include "Game_Object.h"

struct Agent : Game_Object
{
	// Inherited via Game_Object
	virtual void Update() = 0;
	virtual void Render() = 0;

private:
	virtual void Sense() = 0;
	virtual void Decide() = 0;
	virtual void Act() = 0;
};


#endif // !__ANIMAL__
