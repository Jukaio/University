// SpriteAnimation.cc

#include "SpriteAnimation.h"
#include "SpriteAtlas.h"
#include "AtlasManager.h"

SpriteAnimation::SpriteAnimation(const char* filename, const char* id)
{
	if (!load(filename, id))
	{
		printf("Error in path");
	}
}

bool SpriteAnimation::load(const char* filename, const char* id)
{
	FILE* stream;
	char* atlasPath = new char[128];
	char* type = new char[32];

	if (fopen_s(&stream, filename, "r") != 0)
		return false;
	if (fscanf_s(stream, "%s", atlasPath, 128) == 0)
		return false;
	if (fscanf_s(stream, "%s", type, 32) == 0)
		return false;

	atlas_.load(atlasPath, id);
	SingletonAtlasManager::Instance()->add(id, atlas_);

	if (!strcmp(type, "looping"))
		_type = LOOPING;
	else if (!strcmp(type, "pingpong"))
		_type = PINGPONG;
	else if (!strcmp(type, "once"))
		_type = PLAYONCE;

	while (!feof(stream))
	{
		Keyframe tempKeyframe;
		if (fscanf_s(stream, "%ld", &tempKeyframe.id_) == 0)
			return false;
		tempKeyframe.duration_ = 0.5f;
		keyframes_.push_back(tempKeyframe);
	}
	fclose(stream);

	return true;
}
