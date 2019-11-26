using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

using States = PlayerStates.Player_State;


public class MovementMechanic : PlayerController
{
    public Vector3 velocity_;
    [SerializeField] private Vector3 acceleration_;
    [SerializeField] private float counter_Deceleration_Factor_;
    [SerializeField] private Vector3 deceleration_;
    [SerializeField] private float max_Speed_x_;
    public int last_Axis_Input_;


    void Awake()
    {
        Init_Default();
    }

    void Update()
    {

    }

    void Init_Default()
    {
        if (counter_Deceleration_Factor_ == 0)
        {
            counter_Deceleration_Factor_ = 1;
        }

    }

    public States Enter_Accerlation(States from, States to, KeyCode move_Left, KeyCode move_Right) //YAY
    {
        int temp_Press = Command.check_Axis_(move_Left, move_Right);
        if (temp_Press != 0)
        {
            last_Axis_Input_ = temp_Press;
            velocity_ += acceleration_;
            transform.position += velocity_ * last_Axis_Input_ * Time.deltaTime;
            return to;
        }
        return from;
    }
    //Rewise functions
    public States Acceleration(States from, States to, States fail, States counter,
                               KeyCode move_Left, KeyCode move_Right)

    { 
        int temp_Press = Command.check_Axis_(move_Left, move_Right);
        if (temp_Press == -last_Axis_Input_)
        {
            last_Axis_Input_ = temp_Press;
            return counter;
        }

        if (temp_Press != 0)
        {
            last_Axis_Input_ = temp_Press;
            velocity_ += acceleration_;
            if (velocity_.x >= max_Speed_x_)
            {
                velocity_.x = max_Speed_x_;
                return to;
            }
            transform.position += velocity_ * last_Axis_Input_ * Time.deltaTime;
            return from;
        }
        return fail;
    }

    public States High_Speed(States from, States to, States counter, KeyCode move_Left, KeyCode move_Right)
    {
        int temp_Press = Command.check_Axis_(move_Left, move_Right);
        if (temp_Press == -last_Axis_Input_)
        {
            last_Axis_Input_ = temp_Press;
            return counter;
        }
        if (temp_Press != 0)
        {
            if (temp_Press == last_Axis_Input_)
            {
                transform.position += velocity_ * last_Axis_Input_ * Time.deltaTime;
                return from;
            }
            last_Axis_Input_ = temp_Press;
        }
        return to;
    }

    public States Deceleration(States from, States to, States fail, States counter, KeyCode move_Left, KeyCode move_Right)
    {
        int temp_Press = Command.check_Axis_(move_Left, move_Right);
        if (-last_Axis_Input_ == temp_Press)
        {
            last_Axis_Input_ = temp_Press;
            return counter;
        }
        if (temp_Press != 0)
        {
            return fail;
        }
        else
        {
            velocity_ -= deceleration_;
            if (velocity_.x <= 0)
            {
                velocity_ = Vector3.zero;
                return to;
            }
            transform.position -= velocity_ * -last_Axis_Input_ * Time.deltaTime;
            return from;
        }
    }

    public States Counterceleration(States from, States to, States fail, States rewind, KeyCode move_Left, KeyCode move_Right)
    {
        print(velocity_);
        int temp_Press = Command.check_Axis_(move_Left, move_Right);
        if (temp_Press == last_Axis_Input_)
        {
            velocity_ -= deceleration_ * counter_Deceleration_Factor_;
            if (velocity_.x >= 0)
            {
                transform.position -= velocity_ * last_Axis_Input_ * Time.deltaTime;
                return from;
            }
            velocity_ = Vector3.zero;
            return to;
        }
        return fail;
    }

}