// Wyvern_Engine.h

#ifndef __WYVERN_ENGINE__
#define __WYVERN_ENGINE__

#include <SDL2/SDL.h>
#include "Wyvern_Game.h"

//System Utilities

struct Wyvern_Engine
{
	Wyvern_Engine();

	void Initialise();
	void Run();
	void Exit();

private:
	Wyvern_Game game_;
};



#endif // !__WYVERN_ENGINE__

