// input_listener.h

#ifndef INPUT_LISTENER_H_INCLUDED
#define INPUT_LISTENER_H_INCLUDED

// forward declare
struct input_state_delta;

struct input_listener
{
   virtual ~input_listener() = default;
   virtual bool on_input(input_state_delta &input) = 0;
};

#endif // INPUT_LISTENER_H_INCLUDED
