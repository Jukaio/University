// Sprite.h

#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include <spinach.h>
#include "SpriteAnimator.h"
#include "SpriteAnimation.h"

struct Sprite
{
   Sprite();
   Sprite(const char* _id);

   void draw();

   void set_position(const spinach_vector2_t &position);
   void set_texture(const spinach_texture_t texture);
   void set_rectangle(const spinach_rect_t &rectangle);
  

   const char* _id;
private:
   void update_positions();
   void update_texcoords();

   spinach_texture_t texture_;

   spinach_vector2_t position_;
   spinach_rect_t rectangle_;
   spinach_vertex_t vertices_[4];
};

#endif // SPRITE_H_INCLUDED
