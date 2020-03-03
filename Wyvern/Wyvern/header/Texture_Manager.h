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
	static void Initialise();

	static bool Add(std::string id, std::string path);
	static Texture_Data* Get(std::string id);

	static void Destroy();

private:

	Resource_Cache<Texture_Data> texture_Cache_;
	Texture_Manager();
	~Texture_Manager();
	static Texture_Manager* instance_;

	static bool initialised_;
};


#endif // !__TEXTURE_MANAGER__
