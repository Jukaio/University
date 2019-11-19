// SpriteAtlas.cc

#include "SpriteAtlas.h"
#include "TextureManager.h"

SpriteAtlas::SpriteAtlas()
{
}

void SpriteAtlas::add(const spinach_rect_t& rectangle)
{
	_spriteRects.push_back(rectangle);
}

bool SpriteAtlas::get(const uint32_t id, spinach_rect_t &rectangle)
{
	rectangle = _spriteRects[id];
   return true;
}

int SpriteAtlas::frames()
{
	return (int)_spriteRects.size();
}

bool SpriteAtlas::load(const char* filename, const char* id)
{
	FILE* stream;
	char* imagePath = new char[128];

	if (fopen_s(&stream, filename, "r") != 0)
		return false;;
	if (fscanf_s(stream, "%s", imagePath, 128) == 0)
		return false;

	SingletonTextureManager::Instance()->load(imagePath, id);

	while (!feof(stream))
	{
		spinach_rect_t tempRect;
		if (fscanf_s(stream, "%ld", &tempRect.x_) == 0)
			return false;;
		if (fscanf_s(stream, "%ld", &tempRect.y_) == 0)
			return false;;
		if (fscanf_s(stream, "%ld", &tempRect.width_) == 0)
			return false;;
		if (fscanf_s(stream, "%ld", &tempRect.height_) == 0)
			return false;;
		add(tempRect);
	}
	fclose(stream);

	return true;
}


void SpriteAtlas::clear()
{
	_spriteRects.clear();
}
