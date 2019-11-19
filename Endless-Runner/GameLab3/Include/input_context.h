// input_context.h

#ifndef INPUT_CONTEXT_H_INCLUDED
#define INPUT_CONTEXT_H_INCLUDED

#include "input_types.h"

#include <vector>
#include <SFML/Window/Event.hpp>

struct input_context
{
   enum class device_type_id
   {
      KEYBOARD,
      MOUSE,
      COUNT,
      INVALID,
   };

   enum class input_type_id
   {
      ACTION,
      STATE,
      COUNT,
      INVALID,
   };

   input_context();

   void bind_action(sf::Mouse::Button button, const input_action_id id);
   void bind_state(sf::Mouse::Button button, const input_state_id id);
   void bind_action(sf::Keyboard::Key key, const input_action_id id);
   void bind_state(sf::Keyboard::Key key, const input_state_id id);

   bool has_action(const device_type_id device_type, const uint32_t device, input_action_id &action);
   bool has_state(const device_type_id device_type, const uint32_t device, input_state_id &state);

private:
   struct binding
   {
      binding();

      void set_action(sf::Mouse::Button button, const input_action_id id);
      void set_action(sf::Keyboard::Key key, const input_action_id id);
      void set_state(sf::Mouse::Button button, const input_state_id id);
      void set_state(sf::Keyboard::Key key, const input_state_id id);

      device_type_id device_type_;
      union
      {
         uint32_t device_id_;
         sf::Mouse::Button button_;
         sf::Keyboard::Key key_;
      };
      input_type_id input_type_;
      uint32_t input_id_;
   };

   std::vector<binding> bindings_;
};

#endif // INPUT_CONTEXT_H_INCLUDED
