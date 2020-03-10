// Texture_Manager.h

#ifndef __TEXTURE_MANAGER__
#define __TEXTURE_MANAGER__

#include "Cache.h"
#include <SDL2/SDL.h>

struct Texture_Data //Make a neat Texture struct which contains Texture and Rect
{
	~Texture_Data()
	{
		if(texture_ != nullptr)
			SDL_DestroyTexture(texture_);
		texture_ = nullptr;
	}

	SDL_Texture* texture_;
	SDL_Rect src_Rect_;
};

struct Texture_Manager
{
	Texture_Manager();
	~Texture_Manager();

	bool Add(std::string id, std::string path);
	Texture_Data* Get(std::string id);

private:
	Resource_Cache<Texture_Data> texture_Cache_;
};


#endif // !__TEXTURE_MANAGER__
