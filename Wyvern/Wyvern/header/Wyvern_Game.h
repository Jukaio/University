// Wyvern_Game.h

#ifndef __WYVERN_GAME__
#define __WYVERN_GAME__

#include "World.h"
#include "Camera.h"
#include "Grid/Grid.h"

struct Wyvern_Game
{

	Wyvern_Game();
	void Enter();
	void Update();
	void Render();
	void Exit();

	World* Get_World();
	Camera* Get_Camera();
	Grid* Get_Grid();
private:

	Grid* grid_;
	World* world_;
	Camera* camera_;
};



#endif // !__WYVERN_GAME__
