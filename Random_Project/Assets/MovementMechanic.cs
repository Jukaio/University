using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

using States = PlayerStates.Player_State;


public class MovementMechanic : MonoBehaviour
{
    public Vector3 velocity_;
    [SerializeField] private Vector3 acceleration_;
    [SerializeField] private float counter_Deceleration_Factor_;
    [SerializeField] private Vector3 deceleration_;
    [SerializeField] private Vector3 max_Speed_;
    public int last_Axis_Input_ = 1;

    void Awake()
    {
        Init_Default();
    }

    void Init_Default()
    {
        if (counter_Deceleration_Factor_ == 0)
        {
            counter_Deceleration_Factor_ = 1;
        }

    }

    //Check Direction Change
    public bool Check_Same_Direction(int old_Direction, int new_Direction)
    {
        if (old_Direction != new_Direction)
            return false;
        return true;
    }

    //Acceleration
    public States Acceleration(States if_No_Press, States if_Reached_Outcome, States if_Continue_Press,
                               KeyCode move_Left, KeyCode move_Right)

    {
        int temp_Press = Command.check_Axis_(move_Left, move_Right);
        if (if_No_Press == States.IDLE)
        {
            last_Axis_Input_ = temp_Press;
        }
        if (temp_Press != 0)
        {
            if (!Check_Same_Direction(last_Axis_Input_, temp_Press))
                return if_No_Press;

            last_Axis_Input_ = temp_Press;
            velocity_ += acceleration_ * Time.deltaTime;
            if (velocity_.x >= max_Speed_.x)
            {
                velocity_.x = max_Speed_.x;
                return if_Reached_Outcome;
            }
            transform.position += velocity_ * last_Axis_Input_ * Time.deltaTime;
            return if_Continue_Press;
        }
        return if_No_Press;
    }

    public void Translate(Vector3 velocity, int direction)
    {
        last_Axis_Input_ = direction;
        velocity_ = velocity;
        last_Axis_Input_ = direction;

        transform.position += velocity_ * direction * Time.deltaTime;
    }


    //Maximal Speed
    public States High_Speed(States if_No_Press, States if_Reverse_Press, States if_Continue_Press, KeyCode move_Left, KeyCode move_Right)
    {
        int temp_Press = Command.check_Axis_(move_Left, move_Right);
        if (temp_Press != 0)
        {
            if (!Check_Same_Direction(last_Axis_Input_, temp_Press))
            {
                return if_Reverse_Press;
            }
            last_Axis_Input_ = temp_Press;
            transform.position += velocity_ * last_Axis_Input_ * Time.deltaTime;
            return if_Continue_Press;
        }
        return if_No_Press;
    }

    //Deceleration
    public States Deceleration(States if_No_Press, States if_Reached_Outcome, States if_Continue_Press, States if_Reverse_Press, KeyCode move_Left, KeyCode move_Right)
    {
        int temp_Press = Command.check_Axis_(move_Left, move_Right);
        if (temp_Press != 0)
        {
            if (!Check_Same_Direction(last_Axis_Input_, temp_Press))
            {
                return if_Reverse_Press;
            }
            return if_Continue_Press;
        }

        if(velocity_.x > max_Speed_.x)
        {
            velocity_ -= deceleration_ * Time.deltaTime;
            transform.position += velocity_ * last_Axis_Input_ * Time.deltaTime;
            return if_No_Press;
        }

        velocity_ -= deceleration_ * Time.deltaTime;
        if (velocity_.x <= 0)
        {
            return if_Reached_Outcome;
        }
        transform.position += velocity_ * last_Axis_Input_ * Time.deltaTime;
        return if_No_Press;
    }
    public States Deceleration(States if_No_Press, States if_Reached_Outcome, States if_Continue_Press, States if_Reverse_Press, float modifier, KeyCode move_Left, KeyCode move_Right)
    {
        int temp_Press = Command.check_Axis_(move_Left, move_Right);
        if (temp_Press != 0)
        {
            if (!Check_Same_Direction(last_Axis_Input_, temp_Press))
            {
                return if_Reverse_Press;
            }
            return if_Continue_Press;
        }

        if (velocity_.x > max_Speed_.x)
        {
            velocity_ -= deceleration_ * modifier *Time.deltaTime;
            transform.position += velocity_ * last_Axis_Input_ * Time.deltaTime;
            return if_No_Press;
        }

        velocity_ -= deceleration_ * Time.deltaTime;
        if (velocity_.x <= 0)
        {
            return if_Reached_Outcome;
        }
        transform.position += velocity_ * last_Axis_Input_ * Time.deltaTime;
        return if_No_Press;
    }

    //Counterceleration
    public States Counterceleration(States if_No_Press, States if_Reached_Outcome, States if_Continue_Press, States if_Reverse_Press, KeyCode move_Left, KeyCode move_Right)
    {
         int temp_Press = Command.check_Axis_(move_Left, move_Right);
        if (temp_Press != 0)
        {
            if (!Check_Same_Direction(last_Axis_Input_, temp_Press))
            {
                if (velocity_.x <= 0)
                {
                    return if_Reached_Outcome;
                }
                velocity_ -= deceleration_ * counter_Deceleration_Factor_ * Time.deltaTime;
                transform.position += velocity_ * last_Axis_Input_ * Time.deltaTime;
                return if_Reverse_Press;
            }
            return if_Continue_Press;
        }
        return if_No_Press;
    }

    public States Counterceleration(States if_No_Press, States if_Reached_Outcome, States if_Continue_Press, States if_Reverse_Press, float modifier, KeyCode move_Left, KeyCode move_Right)
    {
        int temp_Press = Command.check_Axis_(move_Left, move_Right);
        if (temp_Press != 0)
        {
            if (!Check_Same_Direction(last_Axis_Input_, temp_Press))
            {
                if (velocity_.x <= 0)
                {
                    return if_Reached_Outcome;
                }
                velocity_ -= deceleration_ * counter_Deceleration_Factor_ * modifier * Time.deltaTime;
                transform.position += velocity_ * last_Axis_Input_ * Time.deltaTime;
                return if_Reverse_Press;
            }
            if (velocity_.x <= max_Speed_.x)
                return if_Continue_Press;
        }
        return if_No_Press;
    }
} //Check direction to hotfix it!