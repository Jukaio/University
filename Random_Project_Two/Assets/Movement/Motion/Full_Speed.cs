using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using Easing;
using Movement;
using Movement_State = Movement.Movement_Manager.Movement_State;

namespace Movement.Motion
{
    class Full_Speed
    {
        static public Movement_State Full_Speed_Movement_State_Handler(GameObject game_Object, 
                                                                       Movement_Manager movement_Manager, 
                                                                       Movement_State from, 
                                                                       Movement_State to, 
                                                                       float direction)
        {
            if (direction != 0)
            {
                game_Object.transform.position += Vector3.right * direction * movement_Manager.velocity_ * Time.deltaTime;
                return from;
            }
            return to;
        }
    }
}
