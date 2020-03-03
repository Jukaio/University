// Wyvern_Game.h

#ifndef __WYVERN_GAME__
#define __WYVERN_GAME__

#include "World.h"

struct Wyvern_Game
{

	Wyvern_Game();
	void Initialise();
	void Update();
	void Render();
	void Exit();

private:
	World* world_;
};



#endif // !__WYVERN_GAME__
