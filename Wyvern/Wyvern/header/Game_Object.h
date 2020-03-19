// Game_Object.h

#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include "Entity.h"
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include "Components/Component.h"


struct Game_Object : Entity
{
	Game_Object() : active_(false) { }
	
	virtual ~Game_Object()
	{

	}

	bool Get_Active() { return active_; }
	void Set_Active(bool active) { active_ = active; }

	// Add Component from Parameter
	template <class T>
	void Add_Component(T* component)
	{
		components_[typeid(T)] = component;
	}

	// Initialise Component and Return
	// Add Component with no parameter
	template <class T>
	T* Add_Component()
	{
		T* temp = new T(this);
		components_[typeid(T)] = temp;
		return temp;
	}
	template <class T, class A>
	T* Add_Component(A* param_a)
	{
		T* temp = new T(this, param_a);
		components_[typeid(T)] = temp;
		return temp;
	}
	template <class T, class A, class B>
	T* Add_Component(A* param_a, B* param_b)
	{
		T* temp = new T(this, param_a, param_b);
		components_[typeid(T)] = temp;
		return temp;
	}

	template <class T>
	T* Get_Component()
	{
		return (T*)components_[typeid(T)];
	}

	void Clear_Components()
	{
		for (auto&& component : components_)
		{
			if (component.second != nullptr)
				delete component.second;
		}

		// clear keys
		components_.clear();
	}

	virtual void Update() = 0;
	virtual void Render() = 0;

private:
	bool active_;
	std::unordered_map<std::type_index, Component*> components_;
};


#endif // !__GAME_OBJECT__
