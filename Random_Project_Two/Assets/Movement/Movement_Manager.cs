using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using Key = Input.Key;
using Player_State = Player_Controller.Player_State;

namespace Movement
{
    class Movement_Manager
    {

        class Axis_Movement
        {
            public enum Axis_Movement_State
            {
                IDLE,
                ACCELERATE,
                FULL_SPEED,
                DECELERATE,
                COUNTERCELERATE,
            }
            public Axis_Movement_State current_Axis_State_;

            Input input_;
            float velocity_, max_Velocity_;
            public float acceleration_;
            public float deceleration_;
            float input_Direction_, last_Direction_;
            public Vector3 axis_;

            Key negative_, positive_;

            public Axis_Movement(Input input, float acceleration, float deceleration, Vector3 axis, Key negative, Key positive)
            {
                input_ = input;
                acceleration_ = acceleration;
                deceleration_ = deceleration;
                axis_ = axis;
                negative_ = negative;
                positive_ = positive;
            }

            public int Set_Input_Direction_For_Frame()
            {
                input_Direction_ = input_.input_on_axis(negative_, positive_);
                if (input_Direction_ != 0)
                    return 1;
                return 0;
            }

            public void Idle()
            {
                if (input_Direction_ != 0)
                {
                    last_Direction_ = input_Direction_;
                    current_Axis_State_ = Axis_Movement_State.ACCELERATE;
                    return;
                }
                return;
            }

            public void Acceleration()
            {
                if (input_Direction_ == last_Direction_)
                {
                    velocity_ += acceleration_ * last_Direction_ * Time.deltaTime;
                    if (Mathf.Abs(velocity_) > max_Velocity_)
                    {
                        velocity_ = max_Velocity_;
                        current_Axis_State_ = Axis_Movement_State.FULL_SPEED;
                        return;
                    }
                    current_Axis_State_ = Axis_Movement_State.DECELERATE;
                }
                return;
            }

            public void Full_Speed()
            {
                if (input_Direction_ != last_Direction_)
                {
                    current_Axis_State_ = Axis_Movement_State.DECELERATE;
                }
            }

            public void Deceleration()
            {
                if (input_Direction_ != last_Direction_)
                {
                    if (Mathf.Abs(velocity_) > 0)
                    {
                        velocity_ -= deceleration_ * last_Direction_ * Time.deltaTime;
                    }
                    velocity_ = 0;
                    current_Axis_State_ = Axis_Movement_State.IDLE;
                    return;
                }
                current_Axis_State_ = Axis_Movement_State.ACCELERATE;
            }

            public void Counterceleration()
            {

            }
        }


        public GameObject game_Object_;

        public float velocity_ = 0;
        public float max_Velocity_ = 5.0f;

        List<Axis_Movement> movement_Axes_ = new List<Axis_Movement>();


        public Movement_Manager(GameObject game_Object)
        {
            game_Object_ = game_Object;
        }


        public bool Activate_Axis(Input input, float acceleration, float deceleration, Vector3 axis, Key axis_Negative, Key axis_Positive)
        {
            foreach (Axis_Movement ax in movement_Axes_)
            {
                if (axis == ax.axis_)
                {
                    MonoBehaviour.print("Axis already exists in context - Movement_Manager.cs; Line 80");
                    return false;
                }
            }
            movement_Axes_.Add(new Axis_Movement(input, acceleration, deceleration, axis, axis_Negative, axis_Positive));
            return true;
        }


        public Player_State Input_Handler(Player_State from, Player_State to)
        {
            int count_Movements = 0;
            foreach (Axis_Movement axis in movement_Axes_)
            {
                count_Movements += axis.Set_Input_Direction_For_Frame();

                switch (axis.current_Axis_State_)
                {
                    case Axis_Movement.Axis_Movement_State.IDLE:
                        axis.Idle();
                        break;

                    case Axis_Movement.Axis_Movement_State.ACCELERATE:
                        axis.Acceleration();
                        break;

                    case Axis_Movement.Axis_Movement_State.FULL_SPEED:
                        axis.Full_Speed();
                        break;

                    case Axis_Movement.Axis_Movement_State.DECELERATE:
                        axis.Deceleration();
                        break;

                    case Axis_Movement.Axis_Movement_State.COUNTERCELERATE:
                        axis.Counterceleration();
                        break;
                }
            }

            if (count_Movements > 0)
                return from;
            return to;
        }
    }
}