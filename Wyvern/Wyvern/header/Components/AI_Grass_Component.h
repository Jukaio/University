// AI_Grass_Component.h

#ifndef __AI_GRASS_COMPONENT__
#define __AI_GRASS_COMPONENT__

#include "AI_Component.h"

struct Grass;
struct Transform_Component;
struct Grid;
struct Wyvern_Game;
struct Vector2;
struct Node;

struct AI_Grass_Component : AI_Component
{
	Grass* grass_;

	AI_Grass_Component(Grass* game_object, float sense_rate, float decide_rate, float act_rate, Wyvern_Game* game);
	~AI_Grass_Component();

	void On_Enable();
	void On_Disable();

private:
	Node* node_;
	Wyvern_Game* game_;
	Grid* grid_;
	Transform_Component* transform_;

	Node* Get_Current_Node();
	//
	int level_;
	int max_Level_;

	// Inherited via AI_Component
	virtual void Sense() final;
	virtual void Decide() final;
	virtual void Act() final;

	void Spread();
	float spread_Rate_;
	float spread_Timer_;

	void Grow();
	float grow_Rate_;
	float grow_Timer_;
};

#endif // !__AI_GRASS_COMPONENT__
