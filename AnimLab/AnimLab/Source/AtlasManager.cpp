//AtlasManager.cpp

#include "AtlasManager.h"

AtlasManager* AtlasManager::_instance = 0;

AtlasManager* AtlasManager::Instance()
{
	if (_instance == 0)
	{
		_instance = new AtlasManager;
	}
	return _instance;
}

void AtlasManager::add(const char* id, SpriteAtlas atlas)
{
	_atlasMap[id] = atlas;
}

SpriteAtlas AtlasManager::get(const char* id)
{
	return _atlasMap[id];
}