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
        static public Movement_State Deceleration_Movement_State_Handler(GameObject game_Object, Movement_Manager movement_Manager, Movement_State from, Movement_State to, float direction)
        {
            if (direction == 0)
            {
                if (movement_Manager.velocity_ < 0)
                {
                    movement_Manager.velocity_ -= movement_Manager.deceleration_ * Time.deltaTime;
                    game_Object.transform.position += Vector3.right * direction * movement_Manager.velocity_ * Time.deltaTime; // Need last direction
                }
                return from;
            }
            return to;
        }
    }
}
