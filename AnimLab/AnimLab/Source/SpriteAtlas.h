// SpriteAtlas.h

#ifndef SPRITE_ATLAS_H_INCLUDED
#define SPRITE_ATLAS_H_INCLUDED

#include <string>
#include <map>
#include <spinach.h>
#include <vector>

struct SpriteAtlas
{
   SpriteAtlas();

   void add(const spinach_rect_t &rectangle);
   bool get(const uint32_t id, spinach_rect_t &rectangle);
   int frames();

   bool load(const char *filename, const char* id);
   void clear();

  

private:
	std::vector<spinach_rect_t> _spriteRects;

};

#endif // SPRITE_ATLAS_H_INCLUDED
