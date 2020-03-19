// Grass.h

#ifndef __GRASS__
#define __GRASS__

#include "Game_Object.h"

struct Transform_Component;
struct Render_Component;
struct Camera;
struct Grid;
struct AI_Grass_Component;
struct Vector2;

struct Grass : Game_Object
{
	static Grass* Alloc_Grass(std::size_t size);
	static void Dealloc_Grass(Grass*& block, std::size_t size);

	Grass(Wyvern_Game* game, Vector2 pos);
	~Grass();
	
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
	AI_Grass_Component* ai_;
	Grid* grid_;
	Transform_Component* transform_;
	Render_Component* render_;
};

#endif // !__SHEEP__
