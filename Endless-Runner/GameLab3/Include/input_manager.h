// input_manager.h

#ifndef INPUT_MANAGER_H_INCLUDED
#define INPUT_MANAGER_H_INCLUDED

#include "input_types.h"
#include "input_state_delta.h"

#include <string>
#include <vector>
#include <list>
#include <map>

#include <SFML/Graphics/RenderWindow.hpp>

// forward declare(s)
struct input_context;
struct input_listener;

struct input_manager
{
   input_manager(sf::RenderWindow &window);
   ~input_manager();

   bool process();

   input_context *create_context(const std::string &ident);
   input_context *get_context(const std::string &ident);
   void push_context(const std::string &ident);
   void pop_context();

   void attach_listener(input_listener *listener);
   void detach_listener(input_listener *listener);
   void dispatch();

private:
   sf::RenderWindow &window_;
   input_state_delta cached_state_;
   std::map<std::string, input_context *> contexts_;
   std::list<input_context *> stack_;
   std::vector<input_listener *> listeners_;
};

#endif // !INPUT_MANAGER_H_INCLUDED
