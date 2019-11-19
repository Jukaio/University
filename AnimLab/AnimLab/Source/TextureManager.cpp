#include "TextureManager.h"

TextureManager* TextureManager::_instance = 0;

TextureManager* TextureManager::Instance()
{
	if (_instance == 0)
	{
		_instance = new TextureManager;
	}
	return _instance;
}

bool TextureManager:: load(const char* filePath, const char* id)
{
	spinach_texture_t texture = spinach_texture_load(filePath);

	if (&texture != 0)
	{
		_textureMap[id] = new spinach_texture_t(texture);
		return true;
	}
	
	return false;
}
