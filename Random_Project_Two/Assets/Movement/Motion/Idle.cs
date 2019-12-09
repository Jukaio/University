using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using Movement;
using Movement_State = Movement.Movement_Manager.Movement_State;

namespace Movement.Motion
{
    class Idle
    {
        static public Movement_State Idle_Movement_State_Handler(Movement_State from, Movement_State to, float direction)
        {
            if (direction != 0)
                return to;
            return from;
        }
    }
}
