using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using Easing;
using Movement;
using Movement_State = Movement.Movement_Manager.Movement_State;

namespace Movement.Motion
{
    class Deceleration
    {
        static public Movement_State Deceleration_Movement_State_Handler(GameObject game_Object, 
                                                                         Movement_Manager movement_Manager, 
                                                                         Movement_State from, 
                                                                         Movement_State back_to, 
                                                                         Movement_State to, 
                                                                         float input_Direction, float last_Direction)
        {
            if (input_Direction != last_Direction)
            {
                if (movement_Manager.velocity_ > 0)
                {
                    movement_Manager.velocity_ -= movement_Manager.deceleration_ * Time.deltaTime;
                    game_Object.transform.position += Vector3.right * last_Direction * movement_Manager.velocity_ * Time.deltaTime; // Need last direction
                    return from;
                }
                movement_Manager.velocity_ = 0;
                return to;
            }
            return back_to;
        }
    }
}
