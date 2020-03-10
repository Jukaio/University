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
		for (auto&& file : cache_)
		{
			if (file.second != nullptr)
				delete file.second;
		}

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

	std::unordered_map<std::string, T*> cache_;
};


#endif // !__CACHE__
