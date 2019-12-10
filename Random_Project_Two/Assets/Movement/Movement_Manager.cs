using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using Movement.Motion;
using Key = Input.Key;
using Player_State = Player_Controller.Player_State;

namespace Movement
{
    class Movement_Manager
    {
        public float last_Direction_ = 0;

        public Movement_Manager(GameObject game_Object, Key axis_Negative, Key axis_Positive)
        {
            game_Object_ = game_Object;
            axis_Negative_ = axis_Negative;
            axis_Positive_ = axis_Positive;
        }

        Key axis_Negative_, axis_Positive_;
        public GameObject game_Object_;

        public float velocity_ = 0;
        public float max_Velocity_ = 5.0f;
        public float acceleration_ = 1;
        public float deceleration_ = 1;

        public enum Movement_State
        {
            IDLE,
            ACCELERATE,
            FULL_SPEED,
            DECELERATE,
            COUNTERCELERATE,
        }
        Movement_State current_Movement_State_;

        public Player_State Input_Handler(Player_State from, Player_State to, Input input, Key key)
        {
            MonoBehaviour.print(current_Movement_State_);
            MonoBehaviour.print("Last Direction: " + last_Direction_);
            if (key != Key.NONE)
                if (key != axis_Negative_ && key != axis_Positive_)
                    return from;

            // Declare default return value
            Player_State return_Player_State = from;

            // Check direction on an axis (-1 to 1)
            float direction = input.input_on_axis(axis_Negative_, axis_Positive_);

            if(!Movement_State_Handler(direction))
                return_Player_State = to;
            return return_Player_State;

        }

        bool Movement_State_Handler(float input_Direction)
        {
            switch (current_Movement_State_)
            {
                case Movement_State.IDLE:
                    current_Movement_State_ = Idle.Idle_Movement_State_Handler(current_Movement_State_,
                                                                               Movement_State.ACCELERATE,
                                                                               input_Direction);
                    last_Direction_ = input_Direction;
                    return false;

                case Movement_State.ACCELERATE:
                    current_Movement_State_ = Acceleration.Acceleration_Movement_State_Handler(game_Object_, this,
                                                                                               Movement_State.ACCELERATE,
                                                                                               Movement_State.DECELERATE,
                                                                                               Movement_State.FULL_SPEED,
                                                                                               input_Direction, last_Direction_, max_Velocity_);
                    return true;

                case Movement_State.FULL_SPEED:
                    current_Movement_State_ = Full_Speed.Full_Speed_Movement_State_Handler(game_Object_, this,
                                                                                           Movement_State.FULL_SPEED,
                                                                                           Movement_State.DECELERATE,
                                                                                           input_Direction);
                    return true;

                case Movement_State.DECELERATE:
                    current_Movement_State_ = Deceleration.Deceleration_Movement_State_Handler(game_Object_, this,
                                                                                               Movement_State.DECELERATE,
                                                                                               Movement_State.ACCELERATE,
                                                                                               Movement_State.IDLE,
                                                                                               input_Direction, last_Direction_);
                    return true;

                case Movement_State.COUNTERCELERATE:
                    
                   break;
            }
            return false;
        }
    }
}
