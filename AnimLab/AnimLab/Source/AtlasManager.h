//AtlasManager.h

#ifndef __AtlasManager__
#define __AtlasManager__

#include <map>
#include "SpriteAtlas.h"

class AtlasManager
{
	static AtlasManager* _instance;
	std::map<const char*, SpriteAtlas> _atlasMap;

public:
	static AtlasManager* Instance();
	void add(const char* id, SpriteAtlas atlas);
	SpriteAtlas get(const char* id);
};
typedef AtlasManager SingletonAtlasManager;


#endif // !__AtlasManager__




