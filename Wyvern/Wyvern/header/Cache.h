// Cache.h

#ifndef __CACHE__
#define __CACHE__

#include <unordered_map>
#include <iostream>
#include <string>

template<class T>
struct Resource_Cache
{
	Resource_Cache() = default;
	~Resource_Cache()
	{
		std::cout << "Cache deleted! \n";
		cache_.clear();
	}

	void Add(std::string id, T* file)
	{
		cache_[id] = file;
	}
	T* Get(std::string id)
	{
		return cache_[id];
	}

	std::unordered_map<std::string, T*>* Get_Cache()
	{
		return cache_;
	}

	std::unordered_map<std::string, T*> cache_;
};


#endif // !__CACHE__
