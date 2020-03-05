// Wyvern_Game.h

#ifndef __WYVERN_GAME__
#define __WYVERN_GAME__

#include "World.h"
#include "Camera.h"

struct Wyvern_Game
{

	Wyvern_Game();
	void Initialise();
	void Update();
	void Render();
	void Exit();


	Camera* Get_Camera();
private:
	World* world_;
	Camera* camera_;
};



#endif // !__WYVERN_GAME__
