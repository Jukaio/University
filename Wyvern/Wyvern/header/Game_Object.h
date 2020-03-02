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
	Game_Object() { }

	~Game_Object()
	{
		// delete object pointers
		for (auto&& component : components_)
		{
			if (component.second != nullptr)
				delete component.second;
		}

		// clear keys
		components_.clear();
	}

	template <class T>
	void Add_Component()
	{
		components_[typeid(T)] = new T(*this);
	}

	template <class T>
	T* Get_Component()
	{
		return (T*)components_[typeid(T)];
	}

	virtual void Update() = 0;
	virtual void Render() = 0;

private:
	std::unordered_map<std::type_index, Component*> components_;
};


#endif // !__GAME_OBJECT__
