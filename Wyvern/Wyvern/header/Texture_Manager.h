// Texture_Manager.h

#ifndef __TEXTURE_MANAGER__
#define __TEXTURE_MANAGER__

#include "Cache.h"

struct SDL_Texture;

struct Texture_Manager
{
	static void Initialise();

	static bool Add(std::string id, std::string path);
	static SDL_Texture* Get(std::string id);

	static void Destroy();
private:
	Resource_Cache<SDL_Texture> texture_Cache_;
	Texture_Manager();
	~Texture_Manager() = default;
	static Texture_Manager* instance_;

	static bool initialised_;
};


#endif // !__TEXTURE_MANAGER__
