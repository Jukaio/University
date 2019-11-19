// SpriteAnimator.h

#ifndef ANIMATOR_H_INCLUDED
#define ANIMATOR_H_INCLUDED


struct Sprite;
struct SpriteAnimation;

struct SpriteAnimator
{
   SpriteAnimator(Sprite &sprite, SpriteAnimation &animation);

   void update(float deltatime);
   void draw();
   
private:
	int frame = 0;
	float frameDuration = 0;
	bool backwards = false;

   Sprite &sprite_;
   SpriteAnimation &animation_;
};

#endif // ANIMATOR_H_INCLUDED
