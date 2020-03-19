// AI_Sheep_Component.h

#ifndef __AI_SHEEP_COMPONENT__
#define __AI_SHEEP_COMPONENT__

#include "AI_Component.h"

struct Sheep;
struct Transform_Component;
struct Grid;
struct Wyvern_Game;
struct Vector2;
struct Node;

struct AI_Sheep_Component : AI_Component
{
	Sheep* sheep_;

	AI_Sheep_Component(Sheep* game_object, float sense_rate, float decide_rate, float act_rate, Wyvern_Game* game);
	~AI_Sheep_Component();

	void On_Enable();
	void On_Disable();

private:
	Node* node_;
	Node* prev_Node_;
	Node* next_Node_;


	Wyvern_Game* game_;
	Grid* grid_;
	Transform_Component* transform_;

	Node* Get_Current_Node();
	Node* Get_Next_Node();

	// Inherited via AI_Component
	virtual void Sense() final;
	virtual void Decide() final;
	virtual void Act() final;

	bool Move_Towards(Vector2 position);
};



#endif // !__AI_SHEEP_COMPONENT__
