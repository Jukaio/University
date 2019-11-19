// endless_runner.cc

#include "endless_runner.h"
#include "input_context.h"

constexpr uint32_t EXIT_CODE  = 0xFFFF;

template <typename T> T min(T a, T b) { return a < b ? a : b; }

static float get_deltatime(sf::Clock &clock)
{
   sf::Time diff = clock.restart();
   float dt = min(diff.asSeconds(), 1.0f / 60.0f);
   return dt;
}

endless_runner::endless_runner()
   : current_state_(GAME_STATE_LOAD)
   , input_manager_(window_)
{
}

bool endless_runner::init()
{
   // note: create a non-resizable window 
   window_.create(sf::VideoMode(1280, 720), 
                  "endless-runner", 
                  sf::Style::Titlebar|sf::Style::Close);

   // note: disable key repeats
   window_.setKeyRepeatEnabled(false);

   // note: enable vertical sync
   window_.setVerticalSyncEnabled(true);

   // note: base input context for global game
   auto context = input_manager_.create_context("base");

   // note: bind an action to the newly created input context
   //       when we press escape we will set the current 
   //       state to be GAME_STATE_QUIT which makes the 
   //       game exit
   context->bind_action(sf::Keyboard::Escape, EXIT_CODE);

   // note: push base context to input stack
   input_manager_.push_context("base");

   // note: register 'this' to receive input
   input_manager_.attach_listener(this);

   // note: preload textures
   texture_cache_.load("assets/sunny-land-files/environment/back.png");
   texture_cache_.load("assets/sunny-land-files/environment/middle.png");
   texture_cache_.load("assets/sunny-land-files/environment/tileset.png");
   texture_cache_.load("assets/sunny-land-files/environment/props.png");

   // note: preload sound buffers

   // note: preload fonts

   return true;
}

void endless_runner::run()
{
   sf::Clock clock;
   while (window_.isOpen())
   {
      // note: calculate delta time
      float deltatime = get_deltatime(clock);

      // note: currently we have a simple 
      if (current_state_ == GAME_STATE_QUIT)
         break;

      // note: the input manager handles the polling of 
      //       all sf::Events and dispatching the changes
      //       in input actions and states to all listeners
      if (!input_manager_.process())
         break;

      // note: here we will eventually draw sprites et al.
      window_.clear();

      window_.display();
   }

   exit();
}

void endless_runner::exit()
{
   window_.close();
}

// input_listener
bool endless_runner::on_input(input_state_delta &input)
{
   if (input.has_action(EXIT_CODE))
   {
      current_state_ = GAME_STATE_QUIT;
      input.eat_action(EXIT_CODE);
   }

   return true;
}
