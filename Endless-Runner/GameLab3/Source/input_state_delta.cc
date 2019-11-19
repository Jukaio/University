// input_state_delta.cc

#include "input_state_delta.h"

bool input_state_delta::has_action(input_action_id id) const
{
   return actions_.find(id) != actions_.end();
}

bool input_state_delta::has_state(input_state_id id) const
{
   return states_.find(id) != states_.end();
}

void input_state_delta::eat_action(input_action_id id)
{
   actions_.erase(id);
}

void input_state_delta::eat_state(input_state_id id)
{
   states_.erase(id);
}
