// Wyvern_Engine.h

#ifndef __WYVERN_ENGINE__
#define __WYVERN_ENGINE__

#include "Input/Input_Handler.h"
#include <SDL2/SDL.h>
#include "Wyvern_Game.h"

//System Utilities

struct Wyvern_Engine
{
	Input_Handler input_Handler_;

	Wyvern_Engine();

	void Initialise();
	void Run();
	void Exit();

private:
	Wyvern_Game game_;
};



#endif // !__WYVERN_ENGINE__

