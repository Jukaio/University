// input_context.cc

#include "input_context.h"

input_context::binding::binding()
   : device_type_(device_type_id::INVALID)
   , input_type_(input_type_id::INVALID)
{
}

void input_context::binding::set_action(sf::Mouse::Button button, const input_action_id id)
{
   device_type_ = device_type_id::MOUSE;
   button_ = button;
   input_type_ = input_type_id::ACTION;
   input_id_ = id;
}

void input_context::binding::set_state(sf::Mouse::Button button, const input_state_id id)
{
   device_type_ = device_type_id::MOUSE;
   button_ = button;
   input_type_ = input_type_id::STATE;
   input_id_ = id;
}

void input_context::binding::set_action(sf::Keyboard::Key key, const input_action_id id)
{
   device_type_ = device_type_id::KEYBOARD;
   key_ = key;
   input_type_ = input_type_id::ACTION;
   input_id_ = id;
}

void input_context::binding::set_state(sf::Keyboard::Key key, const input_state_id id)
{
   device_type_ = device_type_id::KEYBOARD;
   key_ = key;
   input_type_ = input_type_id::STATE;
   input_id_ = id;
}

input_context::input_context()
{
}

void input_context::bind_action(sf::Mouse::Button button, const input_action_id id)
{
   binding binding;
   binding.set_action(button, id);
   bindings_.push_back(binding);
}

void input_context::bind_action(sf::Keyboard::Key key, const input_action_id id)
{
   binding binding;
   binding.set_action(key, id);
   bindings_.push_back(binding);
}

void input_context::bind_state(sf::Mouse::Button button, const input_state_id id)
{
   binding binding;
   binding.set_state(button, id);
   bindings_.push_back(binding);
}

void input_context::bind_state(sf::Keyboard::Key key, const input_state_id id)
{
   binding binding;
   binding.set_state(key, id);
   bindings_.push_back(binding);
}

bool input_context::has_action(const device_type_id device,
                               const uint32_t id,
                               input_action_id &action)
{
   for (const auto &binding : bindings_)
   {
      if (binding.device_type_ == device &&
          binding.device_id_ == id &&
          binding.input_type_ == input_type_id::ACTION)
      {
         action = binding.input_id_;
         return true;
      }
   }

   return false;
}

bool input_context::has_state(const device_type_id device,
                              const uint32_t id,
                              input_state_id &state)
{
   for (const auto &binding : bindings_)
   {
      if (binding.device_type_ == device &&
          binding.device_id_ == id &&
          binding.input_type_ == input_type_id::STATE)
      {
         state = binding.input_id_;
         return true;
      }
   }

   return false;
}
