// Game_Object.h

#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include "Entity.h"

struct Collider;

struct Game_Object : Entity
{
private:
	std::unordered_map<std::type_index, Component*> component_Map_;

public:
	Game_Object();
	~Game_Object();

	template <class T>
	void Add_Component();

	template <class T>
	T* Get_Component();

	virtual void Update();
	virtual void Render();
};


#endif // !__GAME_OBJECT__
