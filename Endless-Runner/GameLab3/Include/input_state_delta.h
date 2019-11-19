// input_state_delta.h

#ifndef INPUT_STATE_DELTA_H_INCLUDED
#define INPUT_STATE_DELTA_H_INCLUDED

#include "input_types.h"

#include <set>

struct input_state_delta
{
   input_state_delta() = default;

   bool has_action(input_action_id id) const;
   bool has_state(input_state_id id) const;

   void eat_action(input_action_id id);
   void eat_state(input_state_id id);

private:
   friend struct input_manager;
   std::set<input_action_id> actions_;
   std::set<input_state_id> states_;
};

#endif // 
