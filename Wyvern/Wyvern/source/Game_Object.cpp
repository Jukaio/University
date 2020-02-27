// Game_Object.cpp

#include "Game_Object.h"
#include "Time.h"
#include "Components/Transform.h"
#include "Components/Render_Component.h"
#include "Components/Input_Component.h"
#include "Vector2.h"

Game_Object::~Game_Object()
{
	// delete object pointers
	for (auto&& component : component_Map_)
	{
		if (component.second != nullptr)
			delete component.second;
	}

	// clear keys
	component_Map_.clear();
}

template <class T>
void Game_Object::Add_Component()
{
	component_Map_[typeid(T)] = new T(*this);
}

template <class T>
T* Game_Object::Get_Component()
{
	return (T*)component_Map_[typeid(T)];
}


Game_Object::Game_Object()
{
	Add_Component<Transform>();
	Add_Component<Render_Component>();
	Add_Component<Input_Component>();

	Get_Component<Transform>()->Set_Position(Vector2(100, 100));
	Get_Component<Transform>()->Set_Size(Vector2(100, 100));
}

void Game_Object::Update()
{
	Get_Component<Input_Component>()->Update();
}

void Game_Object::Render()
{
	Get_Component<Render_Component>()->Render_Square();
}

