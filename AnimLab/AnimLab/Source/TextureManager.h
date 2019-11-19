//TextureManager.h

#ifndef __TextureManager__
#define __TextureManager__

#include <spinach.h>
#include <map>

struct TextureManager
{
	static TextureManager* Instance();

	bool load(const char* filePath, const char* id);
	spinach_texture_t* getTexture(const char* id)
	{
		return _textureMap[id];
	}

private:
	static TextureManager* _instance;
	std::map<const char*, spinach_texture_t*> _textureMap;
};
typedef TextureManager SingletonTextureManager;

#endif // !__TextureManager__





