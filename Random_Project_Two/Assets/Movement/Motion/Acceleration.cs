using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using Easing;
using Movement;
using Movement_State = Movement.Movement_Manager.Movement_State;

namespace Movement.Motion
{
    class Acceleration
    {
        //static EasingFunction.Function Ease = EasingFunction.GetEasingFunction(EasingFunction.Ease.EaseInSine);

        //public static float Raise_Velocity(float target, float t, float speed)
        //{
        //    double temp = Ease(t) * speed;

        //    return target * (float)temp;
        //}
        static public Movement_State Acceleration_Movement_State_Handler(GameObject game_Object, 
                                                                         Movement_Manager movement_Manager, 
                                                                         Movement_State from, 
                                                                         Movement_State back_to, 
                                                                         Movement_State to, 
                                                                         float direction, float last_Direction, float max_Velocity)
        {
            if (direction == last_Direction)
            {
                movement_Manager.velocity_ += movement_Manager.acceleration_ * Time.deltaTime;
                if (movement_Manager.velocity_ >= max_Velocity)
                {
                    movement_Manager.velocity_ = max_Velocity;
                    return to;
                }
                game_Object.transform.position += Vector3.right * direction * movement_Manager.velocity_ * Time.deltaTime;
                return from;
            }
            return back_to;
        }
    }
}


