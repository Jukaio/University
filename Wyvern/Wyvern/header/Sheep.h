// Sheep.h

#ifndef __SHEEP__
#define __SHEEP__

#include "Game_Object.h"

struct Transform_Component;
struct Render_Component;
struct Camera;
struct Grid;
struct AI_Sheep_Component;

struct Sheep : Game_Object
{
	Sheep(Wyvern_Game* game);
	~Sheep();

	// Loop
	virtual void Update() override;
	virtual void Render() override;

	//Methods
	void Enable();
	void Disable();

	Grid* Get_Grid();
	Transform_Component* Get_Transform();
	Render_Component* Get_Render();

private:
	AI_Sheep_Component* ai_;
	Grid* grid_;
	Transform_Component* transform_;
	Render_Component* render_;
};

#endif // !__GRASS__
