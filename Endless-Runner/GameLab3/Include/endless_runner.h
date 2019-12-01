// endless_runner.h

#ifndef ENDLESS_RUNNER_H_INCLUDED
#define ENDLESS_RUNNER_H_INCLUDED

#include "input_listener.h"
#include "input_manager.h"
#include "resource_caches.h"
#include <SFML/Graphics.hpp>
#include "Parallax.h"
#include <SFML/Graphics/RenderWindow.hpp>

enum state_type_id
{
   GAME_STATE_LOAD,
   GAME_STATE_MENU,
   GAME_STATE_PLAY,
   GAME_STATE_DEAD,
   GAME_STATE_QUIT,
};

struct endless_runner : input_listener
{
   endless_runner();

   bool init();
   void run();

//private:
   void exit();

   // input listener interface
   bool on_input(input_state_delta &input);

//private:
   sf::RenderWindow window_;
   state_type_id current_state_;
   input_manager input_manager_;

   texture_cache texture_cache_;
   sound_buffer_cache sound_buffer_cache_;
   font_cache font_cache_;

   Parallax* parallax_ = 0;

   sf::Sprite alpha_Sprite_;
   sf::Sprite beta_Sprite_;
};

#endif // ENDLESS_RUNNER_H_INCLUDED
