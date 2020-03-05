// Service.h

#ifndef __SERVICE__
#define __SERVICE__

#include <cassert>
#include <typeindex>
#include <typeinfo>

template <typename T>
struct Service
{
	static void Set(T* instance) 
	{ 
		if (instance_ == nullptr)
		{
			instance_ = instance;
			return;
		}
		std::type_index id = typeid(T);
		assert(false);
	}
	static T* Get() { return instance_; }
	static void Clean() 
	{ 
		if(instance_ != nullptr)
			delete instance_;
		instance_ = nullptr;
	}

private:
	static T* instance_;
	Service() {}
};

#endif // !__SERVICE__

template <typename T>
T* Service<T>::instance_ = nullptr;