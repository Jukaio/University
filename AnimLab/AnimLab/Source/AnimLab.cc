// AnimLab.cc


#include <spinach.h>
#include "Sprite.h"
#include "SpriteAnimator.h"
#include "SpriteAtlas.h"
#include <chrono>

//const int FPS = 60;
//const float DELAY_TIME = 1000.0f / FPS;

int main(int argc, char **argv)
{
	/*unsigned int frameStart, frameTime = 0;*/
   if (!spinach_window_init("AnimLab", 1280, 720))
      return 0;
   
   SpriteAnimation animation("Assets/animation/cherry.txt", "cherry");
   Sprite sprite("cherry");
   SpriteAnimator animator(sprite, animation); // put that shit in a class maybe

   SpriteAnimation animation2("Assets/animation/frog-idle.txt", "frogi");
   Sprite sprite2("frogi");
   SpriteAnimator animator2(sprite2, animation2);

   SpriteAnimation animation3("Assets/animation/frog-jump.txt", "frogj");
   Sprite sprite3("frogj");
   SpriteAnimator animator3(sprite3, animation3);

   auto tp = std::chrono::steady_clock::now();

   //CLEAN UP MORON!!!
   //UPDATE TIME//KEYFRAMES SHIT

   sprite.set_position(spinach_vector2_t{ 100, 100 });
   sprite2.set_position( spinach_vector2_t{200, 200} );
   sprite3.set_position(spinach_vector2_t{ 300, 300 });
   while (spinach_window_process())
   { 
	  /*frameStart = spinach_get_ticks();*/

      if (spinach_key_released(KEY_ESCAPE))
         break;
	  
	  float dt;
	  {
		  const auto new_tp = std::chrono::steady_clock::now();
		  dt = std::chrono::duration<float>(new_tp - tp).count();
		  tp = new_tp;
	  }

	  animator.update(dt);
	  animator2.update(dt);
	  animator3.update(dt);

	  animator.draw();
	  animator2.draw();
	  animator3.draw();

	 /*if (frameTime < DELAY_TIME)
		 std::this_thread::sleep_for(std::chrono::milliseconds(int (DELAY_TIME - frameTime)));

	 frameTime = spinach_get_ticks() - frameStart;*/
   }

   return 0;
}
