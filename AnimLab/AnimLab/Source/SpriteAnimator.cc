// SpriteAnimator.cc

#include "SpriteAnimator.h"
#include "Sprite.h"
#include "SpriteAnimation.h"
#include "AtlasManager.h"
#include "TextureManager.h"

SpriteAnimator::SpriteAnimator(Sprite &sprite, SpriteAnimation &animation)
   : sprite_(sprite)
   , animation_(animation)
{
	
}

void SpriteAnimator::update(float deltatime)
{
	frameDuration = frameDuration - deltatime;
	if (frameDuration > 0)
		return;

	spinach_rect_t tempRect;
	SingletonAtlasManager::Instance()->get(sprite_._id).get(animation_.getKeyFrameID(frame), tempRect);
	sprite_.set_rectangle(tempRect);

	switch (animation_._type)
	{
		case SpriteAnimation::LOOPING:

			if (frame >= SingletonAtlasManager::Instance()->get(sprite_._id).frames() - 1)
				frame = 0;
			else
				frame++;
			break;

		case SpriteAnimation::PINGPONG:
			if (frame >= SingletonAtlasManager::Instance()->get(sprite_._id).frames() - 1)
				backwards = true;
			else if (frame == 0 && backwards)
				backwards = false;

			if (!backwards)
				frame++;
			else
				frame--;
			break;

		case SpriteAnimation::PLAYONCE:
			if (frame >= SingletonAtlasManager::Instance()->get(sprite_._id).frames() - 1)
				return;
			else
				frame++;
			break;
	}
	frameDuration = animation_.getKeyFrameDuration(frame);
}

void SpriteAnimator::draw()
{
   sprite_.draw();
}
