// endless_runner.h

#ifndef ENDLESS_RUNNER_H_INCLUDED
#define ENDLESS_RUNNER_H_INCLUDED

#include "input_listener.h"
#include "input_manager.h"
#include "resource_caches.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Parallax.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Player.h"
#include "Object.h"

enum state_type_id
{
   GAME_STATE_LOAD,
   GAME_STATE_MENU,
   GAME_STATE_PLAY,
   GAME_STATE_DEAD,
   GAME_STATE_QUIT,
   GAME_STATE_PAUSE
};

struct endless_runner : input_listener
{
   endless_runner();

   bool init();
   void create_Game();
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

   Parallax* parallax_Deep_Layer_ = 0;
   Parallax* parallax_Middle_Layer_ = 0;
   Parallax* parallax_Front_Layer_ = 0;
   Parallax* parallax_Pretty_Stuff_ = 0;

   sf::Sprite obstacles_[3];

   Object* gem_ = 0;

   sf::Sound sound_Death_;
   sf::Sound sound_Jump_;
   sf::Sound sound_Boing_;
   sf::Music background_Music_;

   sf::Text menu_Text_;
   sf::Text highscore_;
   float score_ = 0;

   float screenshake_duration = 1.0f;
   int variable = 1;
   int shake_direction_ = 1;
   bool first_shake = false;
   Player* player_ = 0;
   bool jumped_ = false;

   float easing_t_ = 0;
   float menu_easing_t_ = 0;
   float text_easing_t_ = 0;
   float pause_easing_t_ = 0;

   sf::View view;

   const sf::Texture* explosion_ = 0;
   sf::Sprite* explosion_Object_ = 0;
   int explosion_frame_ = 0;
   float hold_explosion_frame_ = 0;

   sf::Sprite alpha_Sprite_;
   sf::Sprite beta_Sprite_;
};

#endif // ENDLESS_RUNNER_H_INCLUDED
