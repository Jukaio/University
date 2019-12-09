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
        public Movement_Manager(GameObject game_Object, Key axis_Negative, Key axis_Positive)
        {
            game_Object_ = game_Object;
            axis_Negative_ = axis_Negative;
            axis_Positive_ = axis_Positive;
        }

        Key axis_Negative_, axis_Positive_;
        public GameObject game_Object_;

        public float velocity_ = 0;
        public float acceleration_ = 1;
        public float deceleration_ = 1;

        public enum Movement_State
        {
            IDLE,
            ACCELERATE,
            HIGH_SPEED,
            DECELERATE,
        }
        Movement_State current_Movement_State_;

        public Player_State Input_Handler(Player_State from, Player_State to, Input input, Key key)
        {
            MonoBehaviour.print(velocity_);
            if (key != Key.NONE)
                if (key != axis_Negative_ && key != axis_Positive_)
                    return from;

            // Declare default return value
            Player_State return_Player_State = from;

            // Check direction on an axis (-1 to 1)
            float direction = input.input_on_axis(axis_Negative_, axis_Positive_);

            if(!Movement_State_Handler(direction))
                return_Player_State = to;

            //if (direction != 0)
            //{
            //    Acceleration(Vector3.right, direction);
            //    return_Player_State = from;
            //}

            //if (velocity_ <= 0)
            //{
            //    return_Player_State = to;
            //}
            return return_Player_State;

        }

        bool Movement_State_Handler(float direction)
        {
            switch (current_Movement_State_)
            {
                case Movement_State.IDLE:
                    current_Movement_State_ = Idle.Idle_Movement_State_Handler(current_Movement_State_, 
                                                                               Movement_State.ACCELERATE, 
                                                                               direction);
                    return false;

                case Movement_State.ACCELERATE:
                    current_Movement_State_ = Acceleration.Acceleration_Movement_State_Handler(game_Object_, this,
                                                                                               Movement_State.ACCELERATE, 
                                                                                               Movement_State.DECELERATE, 
                                                                                               direction);
                    return true;

                case Movement_State.HIGH_SPEED:

                    return true;

                case Movement_State.DECELERATE:
                    current_Movement_State_ = Deceleration.Deceleration_Movement_State_Handler(game_Object_, this,
                                                                                               Movement_State.DECELERATE,
                                                                                               Movement_State.ACCELERATE,
                                                                                               direction);
                    return true;
            }
            return false;
        }

        void Object_Movement(Vector3 axis, float direction)
        {
            game_Object_.transform.position += axis * velocity_ * direction * Time.deltaTime;
        }

        //void Acceleration(Vector3 axis, float direction)
        //{
        //    velocity_ += acceleration_;
        //    Object_Movement(axis, direction);
        //}

        //void Deceleration(Vector3 axis, float direction)
        //{
        //    velocity_ -= deceleration_;
        //    Object_Movement(axis, direction);
        //}

    }
}
