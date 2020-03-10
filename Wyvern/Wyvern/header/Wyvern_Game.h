// Wyvern_Game.h

#ifndef __WYVERN_GAME__
#define __WYVERN_GAME__

#include "World.h"
#include "Camera.h"

struct Wyvern_Game
{

	Wyvern_Game();
	void Enter();
	void Update();
	void Render();
	void Exit();


	Camera* Get_Camera();
private:
	void Create_Interface();
	void Create_World();

	World* world_;
	Camera* camera_;
};



#endif // !__WYVERN_GAME__
