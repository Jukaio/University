// input_manager.cc

#include "input_manager.h"
#include "input_context.h"
#include "input_listener.h"

#include <cassert>

input_manager::input_manager(sf::RenderWindow &window)
   : window_(window)
{
}

input_manager::~input_manager()
{
   for (auto& iter : contexts_)
      delete iter.second;
   contexts_.clear();

   stack_.clear();
   listeners_.clear();
}

bool input_manager::process()
{
   sf::Event event;
   while (window_.pollEvent(event))
   {
      if (event.type == sf::Event::Closed)
         return false;

      // note: translate SFML events to input binding
      input_context::device_type_id device_type = input_context::device_type_id::INVALID;
      uint32_t device_id = 0;

      bool pressed = false;

      switch (event.type)
      {
         case sf::Event::MouseButtonPressed:
         case sf::Event::MouseButtonReleased:
         {
            pressed = (event.type == sf::Event::MouseButtonPressed);

            device_type = input_context::device_type_id::MOUSE;
            device_id = event.mouseButton.button;
         } break;
         case sf::Event::KeyPressed:
         case sf::Event::KeyReleased:
         {
            pressed = (event.type == sf::Event::KeyPressed);

            device_type = input_context::device_type_id::KEYBOARD;
            device_id = event.key.code;
         } break;
         default:
         {
            continue;
         } break;
      }

      // note: find if we have a binding in any context for event
      for (const auto &context : stack_)
      {
         input_state_id state = 0;
         input_action_id action = 0;

         if (pressed)
         {
            if (context->has_action(device_type, device_id, action))
            {
               cached_state_.actions_.insert(action);
               break;
            }
         }

         if (context->has_state(device_type, device_id, state))
         {
            if (!pressed)
               cached_state_.states_.erase(state);
            else
               cached_state_.states_.insert(state);
            break;
         }
      }
   }

   // note: we are now done, we can tell everyone 
   //       interested the result
   dispatch();

   return true;
}

input_context *input_manager::create_context(const std::string &ident)
{
   assert(contexts_.find(ident) == contexts_.end());

   input_context *context = new input_context;
   contexts_.insert(std::pair<std::string, input_context*>(ident, context));

   return context;
}

input_context *input_manager::get_context(const std::string &ident)
{
   auto iter = contexts_.find(ident);
   assert(iter != contexts_.end());

   return iter->second;
}

void input_manager::push_context(const std::string &ident)
{
   auto iter = contexts_.find(ident);
   if (iter == contexts_.end())
      return;

   stack_.push_front(iter->second);
}

void input_manager::pop_context()
{
   stack_.pop_front();
}

void input_manager::attach_listener(input_listener *listener)
{
   listeners_.push_back(listener);
}

void input_manager::detach_listener(input_listener *listener)
{
   auto iter = listeners_.begin();
   while (iter != listeners_.end())
   {
      if (*iter == listener)
      {
         listeners_.erase(iter);
         break;
      }

      ++iter;
   }
}

void input_manager::dispatch()
{
   input_state_delta state = cached_state_;

   // note: let the everyone interested 
   //       know about the input actions 
   //       and states
   for (auto&& listener : listeners_)
   {
      listener->on_input(state);
   }

   // note: clear cache
   cached_state_.actions_.clear();
}
