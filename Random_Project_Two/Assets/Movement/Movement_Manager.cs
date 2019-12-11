using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using Key = Input.Key;
using Player_State = Player_Controller.Player_State;

namespace Movement
{
    class Movement_Manager
    {
        //Get the Inputs
        //Decide what to do with Inputs
        //Act accordingly
        //Clear Inputs
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
            public float velocity_, max_Velocity_ = 10.0f;
            public float acceleration_;
            public float deceleration_;
            public float input_Direction_ = 0; 
            public float last_Direction_;
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

            public void Handle_Input_For_Frame(Key key)
            {
                if (key == negative_)
                    input_Direction_ -= 1.0f;
                if (key == positive_)
                    input_Direction_ += 1.0f;
                else
                    input_Direction_ += 0.0f;
            }

            public Player_State Idle()
            {
                if (input_Direction_ != 0)
                {
                    last_Direction_ = input_Direction_;
                    current_Axis_State_ = Axis_Movement_State.ACCELERATE;
                    return Player_State.MOVEMENT;
                }
                return Player_State.ROOT;
            }

            public int Acceleration()
            {
                if (input_Direction_ == last_Direction_)
                {
                    velocity_ += acceleration_ * last_Direction_ * Time.deltaTime;
                    if (Mathf.Abs(velocity_) > max_Velocity_)
                    {
                        velocity_ = max_Velocity_ * last_Direction_;
                        current_Axis_State_ = Axis_Movement_State.FULL_SPEED;
                        return 1;
                    }
                    return 1;
                }
                current_Axis_State_ = Axis_Movement_State.DECELERATE;
                return 1;
            }

            public int Full_Speed()
            {
                if (input_Direction_ != last_Direction_)
                {
                    current_Axis_State_ = Axis_Movement_State.DECELERATE;
                }
                return 1;
            }

            public int Deceleration()
            {
                if (input_Direction_ != last_Direction_)
                {
                    velocity_ -= deceleration_ * last_Direction_ * Time.deltaTime;
                    if (input_Direction_ != 0)
                        velocity_ += acceleration_ * -last_Direction_ * Time.deltaTime;


                    if (velocity_ * last_Direction_ <= 0)
                    {
                        velocity_ = 0;
                        last_Direction_ = 0;
                        current_Axis_State_ = Axis_Movement_State.IDLE;
                        return 1;
                    }
                    return 1;
                }
                current_Axis_State_ = Axis_Movement_State.ACCELERATE;
                return 1;
            }

            public int Counterceleration()
            {
                return 0;
            }

            public void Clear_Axis()
            {
                input_Direction_ = 0;
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

        public void Input_Handler(Key key) // Sets "Dual" Input
        {
            foreach (Axis_Movement axis in movement_Axes_)
            {
                axis.Handle_Input_For_Frame(key);
            }
        }
        int count_Movements = 0;
        public Player_State Input_Handler(Player_State from, Player_State to)
        {

            MonoBehaviour.print(movement_Axes_[1].input_Direction_ + " " + movement_Axes_[1].last_Direction_ + " " + movement_Axes_[1].current_Axis_State_);
            foreach (Axis_Movement axis in movement_Axes_)
            {
                switch (axis.current_Axis_State_)
                {
                    case Axis_Movement.Axis_Movement_State.IDLE:
                        axis.Idle();
                        break;

                    case Axis_Movement.Axis_Movement_State.ACCELERATE:
                        count_Movements += axis.Acceleration();
                        break;

                    case Axis_Movement.Axis_Movement_State.FULL_SPEED:
                        count_Movements += axis.Full_Speed();
                        break;

                    case Axis_Movement.Axis_Movement_State.DECELERATE:
                        count_Movements += axis.Deceleration();
                        break;

                    case Axis_Movement.Axis_Movement_State.COUNTERCELERATE:
                        count_Movements += axis.Counterceleration();
                        break;
                }
            }
            return from;
        }

        public void Translate()
        {
            foreach (Axis_Movement axis in movement_Axes_)
            {
                game_Object_.transform.position += axis.velocity_ * axis.axis_ * Time.deltaTime;
            }
        }

        public void Clear_Movement_Manager()
        {
            foreach (Axis_Movement axis in movement_Axes_)
            {
                axis.Clear_Axis();
            }
        }
    }
}