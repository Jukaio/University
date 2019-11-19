// SpriteAnimation.h

#ifndef SPRITE_ANIMATION_H_INCLUDED
#define SPRITE_ANIMATION_H_INCLUDED

#include <spinach.h>
#include <vector>
#include "SpriteAtlas.h"

struct SpriteAtlas;

struct SpriteAnimation
{
   enum Type
   {
      LOOPING,
      PINGPONG,
      PLAYONCE,
   };
   Type _type;

   bool load(const char* filename, const char* id);
   SpriteAnimation(const char* filename, const char* id);
   int getKeyFrameID(int id)
   {
	   return keyframes_[id].id_;
   }
   float getKeyFrameDuration(int id)
   {
	   return keyframes_[id].duration_;
   }

private:
	SpriteAtlas atlas_;
	const char* _textureID;
   // note: this is just an example of
   //       how a "keyframe" might look like
   struct Keyframe
   {
      int id_;
      float duration_;
   };

   std::vector<Keyframe> keyframes_;

};

#endif // SPRITE_ANIMATION_H_INCLUDED
