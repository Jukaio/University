using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using Key = Custom_Input.Key;

namespace Axes
{
    class Axis
    {
        public enum Axis_State
        {
            IDLE,
            ACCELERATE,
            FULL_SPEED,
            DECELERATE,
            COUNTERCELERATE,
        }
        public Axis_State current_Axis_State_;

        public float velocity_, max_Velocity_ = 10.0f;
        public float acceleration_;
        public float deceleration_;
        public float input_Direction_ = 0;
        public float last_Direction_;
        public Vector3 axis_;
        Key negative_, positive_;

        public Axis(float acceleration, float deceleration, Vector3 axis, Key negative, Key positive)
        {
            acceleration_ = acceleration;
            deceleration_ = deceleration;
            axis_ = axis;
            negative_ = negative;
            positive_ = positive;
        }

        public int Handle_Input_For_Frame(Key key)
        {
            if (key == negative_)
                input_Direction_ -= 1.0f;
            if (key == positive_)
                input_Direction_ += 1.0f;
            else
                input_Direction_ += 0.0f;

            return (int) Mathf.Abs(input_Direction_);
        }


        public void Idle()
        {
            if (input_Direction_ != 0)
            {
                last_Direction_ = input_Direction_;
                current_Axis_State_ = Axis_State.ACCELERATE;
                return;
            }
            return;
        }

        public void Acceleration(Axis_State if_Max_Velocity, Axis_State if_Release)
        {
            if (input_Direction_ == last_Direction_)
            {
                velocity_ += acceleration_ * last_Direction_ * Time.deltaTime;
                if (Mathf.Abs(velocity_) > max_Velocity_)
                {
                    velocity_ = max_Velocity_ * last_Direction_;
                    current_Axis_State_ = if_Max_Velocity;
                    return;
                }
                return;
            }
            current_Axis_State_ = if_Release;
            return;
        }
        public void Full_Speed(Axis_State if_Release)
        {
            if (input_Direction_ != last_Direction_)
            {
                current_Axis_State_ = if_Release;
            }
            return;
        }
        public void Deceleration(Axis_State zero_Velocity, Axis_State if_Pressed)
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
                    current_Axis_State_ = zero_Velocity;
                    return;
                }
                return;
            }
            current_Axis_State_ = if_Pressed;
            return;
        }
        public void Clear_Axis()
        {
            input_Direction_ = 0;
        }

    }
}
