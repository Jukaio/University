﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Axes;

using Key = Input.Key;

using Player_State = Player_Controller.Player_State;

namespace Movement
{
    class Force_Manager
    {
        public GameObject game_Object_;
        List<Axis> movement_Axes_ = new List<Axis>();


        public Force_Manager(GameObject game_Object)
        {
            game_Object_ = game_Object;
        }

        public bool Activate_Axis(Input input, float acceleration, float deceleration, Vector3 axis, Key axis_Negative, Key axis_Positive)
        {
            foreach (Axis ax in movement_Axes_)
            {
                if (axis == ax.axis_)
                {
                    MonoBehaviour.print("Axis already exists in context - Movement_Manager.cs; Line 80");
                    return false;
                }
            }
            movement_Axes_.Add(new Axis(acceleration, deceleration, axis, axis_Negative, axis_Positive));
            return true;
        }

        public void Input_Handler(Key key) // Sets "Dual" Input
        {
            foreach (Axis axis in movement_Axes_)
            {
                axis.Handle_Input_For_Frame(key);
            }
        }

        int count_Idle_ = 0;
        public Player_State Input_Handler(Player_State from, Player_State to)
        {
            foreach (Axis axis in movement_Axes_)
            {
                switch (axis.current_Axis_State_)
                {
                    case Axis.Axis_State.IDLE:
                        axis.Idle();
                        count_Idle_++;
                        break;

                    case Axis.Axis_State.ACCELERATE:
                        axis.Acceleration(Axis.Axis_State.DECELERATE, Axis.Axis_State.ACCELERATE);
                        break;

                    case Axis.Axis_State.FULL_SPEED:
                        axis.Full_Speed(Axis.Axis_State.DECELERATE);
                        break;

                    case Axis.Axis_State.DECELERATE:
                        axis.Deceleration(Axis.Axis_State.IDLE, Axis.Axis_State.DECELERATE);
                        break;

                }
            }
            if (count_Idle_ == movement_Axes_.Count)
                return to;
            return from;
        }

        public void Act_Movement()
        {
            foreach (Axis axis in movement_Axes_)
            {
                game_Object_.transform.position += axis.velocity_ * axis.axis_ * Time.deltaTime;
            }
        }

        public void Clear_Movement_Manager()
        {
            count_Idle_ = 0;
            foreach (Axis axis in movement_Axes_)
            {
                axis.Clear_Axis();
            }
        }
    }
}