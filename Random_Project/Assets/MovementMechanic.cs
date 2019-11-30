using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

using States = PlayerStates.Player_State;


public class MovementMechanic : MonoBehaviour
{
    
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

    ////////////////////////////////////
    //// Movement and Configuration ////
    ////////////////////////////////////

    //Modifiable Data
    public float velocity_;
    [SerializeField] private float acceleration_;
    [SerializeField] private float deceleration_;
    [SerializeField] private float counter_Deceleration_Factor_;
    [SerializeField] private float max_Speed_;

    //Data
    private int last_Axis_Input_ = 1;
    public Vector3 last_Temp_Press = Vector3.right;

    private enum Axes
    {
        x, y, z,
    }
    [SerializeField] Axes first_Axis_;
    [SerializeField] Axes second_Axis_;

    //Check Direction Change
    public bool Check_Same_Direction(int old_Direction, int new_Direction)
    {
        if (old_Direction != new_Direction)
            return false;
        return true;
    }
    public bool Check_Direction(Vector3 current, Vector3 previous)
    {
        return false;
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
            if (velocity_ >= max_Speed_)
            {
                velocity_ = max_Speed_;
                return if_Reached_Outcome;
            }
            transform.position += Vector3.right * velocity_ * last_Axis_Input_ * Time.deltaTime;
            return if_Continue_Press;
        }
        return if_No_Press;
    }

    public States Acceleration(States if_No_Press, States if_Reached_Outcome, States if_Continue_Press, States if_Reverse_Press,
                               KeyCode x_minus, KeyCode x_plus, KeyCode y_minus, KeyCode y_plus)
    {
        Vector3 temp = Command.check_Both_DPad_Axes_(x_minus, x_plus, y_minus, y_plus);
        temp = Assign_Axes(temp, first_Axis_, second_Axis_);

        if (if_No_Press == States.IDLE)
        {
            last_Temp_Press = temp;
        }

        if (temp != Vector3.zero)
        {
            if (temp != last_Temp_Press)
            {
                return if_Reverse_Press;
            }

            last_Temp_Press = temp;
            velocity_ += acceleration_ * Time.deltaTime; ;
            
            if (velocity_ >= max_Speed_)
            {
                velocity_ = max_Speed_;
                return if_Reached_Outcome;
            }

            transform.position += velocity_ * last_Temp_Press * Time.deltaTime;
            return if_Continue_Press;
        }
        return if_No_Press;
    }

    //Assign correct data to correct axis
    Vector3 Assign_Axis(float data, Axes axis)
    {
        Vector3 temp = Vector3.zero;
        switch (axis)
        {
            case Axes.x:
                temp.x = data;
                break;
            case Axes.y:
                temp.y = data;
                break;
            case Axes.z:
                temp.z = data;
                break;
        }
        return temp;
    }
    Vector3 Assign_Axes(Vector3 data, Axes first_Axis, Axes second_Axis)
    {
        Vector3 temp = Vector3.zero;
        temp += Assign_Axis(data.x, first_Axis);
        temp += Assign_Axis(data.y, second_Axis);
        return temp;
    }
    Vector3 Assign_Axes(float first_Data, float second_Data, Axes first_Axis, Axes second_Axis)
    {
        Vector3 temp = Vector3.zero;
        temp += Assign_Axis(first_Data, first_Axis);
        temp += Assign_Axis(second_Data, second_Axis);
        return temp;
    }

    //Maximal Speed
    public States High_Speed(States if_No_Press, States if_Reverse_Press, States if_Continue_Press, 
                             KeyCode move_Left, KeyCode move_Right)
    {
        int temp_Press = Command.check_Axis_(move_Left, move_Right);
        if (temp_Press != 0)
        {
            if (!Check_Same_Direction(last_Axis_Input_, temp_Press))
            {
                return if_Reverse_Press;
            }
            last_Axis_Input_ = temp_Press;
            transform.position += Vector3.right * velocity_ * last_Axis_Input_ * Time.deltaTime;
            return if_Continue_Press;
        }
        return if_No_Press;
    }
    public States High_Speed(States if_No_Press, States if_Reverse_Press, States if_Continue_Press, 
                             KeyCode x_minus, KeyCode x_plus, KeyCode y_minus, KeyCode y_plus)
    {
        Vector3 temp = Command.check_Both_DPad_Axes_(x_minus, x_plus, y_minus, y_plus);
        temp = Assign_Axes(temp, first_Axis_, second_Axis_).normalized;

        if (temp != Vector3.zero)
        {
            if (temp != last_Temp_Press)
            {
                return if_Reverse_Press;
            }

            last_Temp_Press = temp;
            transform.position += velocity_ * temp * Time.deltaTime;
            return if_Continue_Press;
        }
        return if_No_Press;
    }

    //Use Max Speed as function, rather than State
    public void Translate(float velocity, int direction)
    {
        last_Axis_Input_ = direction;
        velocity_ = velocity;
        last_Axis_Input_ = direction;

        transform.position += Vector3.right * velocity_ * direction * Time.deltaTime;
    }

    //Deceleration
    public States Deceleration(States if_No_Press, States if_Reached_Outcome, States if_Continue_Press, States if_Reverse_Press, 
                               KeyCode move_Left, KeyCode move_Right)
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

        if(velocity_ > max_Speed_)
        {
            velocity_ -= deceleration_ * Time.deltaTime;
            transform.position += Vector3.right * velocity_ * last_Axis_Input_ * Time.deltaTime;
            return if_No_Press;
        }

        velocity_ -= deceleration_ * Time.deltaTime;
        if (velocity_ <= 0)
        {
            return if_Reached_Outcome;
        }
        transform.position += Vector3.right * velocity_ * last_Axis_Input_ * Time.deltaTime;
        return if_No_Press;
    }
    public States Deceleration(States if_No_Press, States if_Reached_Outcome, States if_Continue_Press, States if_Reverse_Press, 
                               float modifier, KeyCode move_Left, KeyCode move_Right)
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

        if (velocity_ > max_Speed_)
        {
            velocity_ -= deceleration_ * modifier *Time.deltaTime;
            transform.position += Vector3.right * velocity_ * last_Axis_Input_ * Time.deltaTime;
            return if_No_Press;
        }

        velocity_ -= deceleration_ * Time.deltaTime;
        if (velocity_ <= 0)
        {
            return if_Reached_Outcome;
        }
        transform.position += Vector3.right * velocity_ * last_Axis_Input_ * Time.deltaTime;
        return if_No_Press;
    }

    public States Deceleration(States if_No_Press, States if_Reached_Outcome, States if_Continue_Press, States if_Reverse_Press,
                               KeyCode x_minus, KeyCode x_plus, KeyCode y_minus, KeyCode y_plus)
    {
        Vector3 temp = Command.check_Both_DPad_Axes_(x_minus, x_plus, y_minus, y_plus);
        temp = Assign_Axes(temp, first_Axis_, second_Axis_);

        if (temp != Vector3.zero)
        {
            if (temp != last_Temp_Press)
            {
                return if_Reverse_Press;
            }

            return if_Continue_Press;
        }

        velocity_ -= deceleration_ * Time.deltaTime;
        if (velocity_ <= 0)
        {
            velocity_ = 0;
            return if_Reached_Outcome;
        }
        velocity_ -= deceleration_ * Time.deltaTime;
        transform.position += velocity_ * last_Temp_Press * Time.deltaTime;
        return if_No_Press;
    }

    //Counterceleration
    public States Counterceleration(States if_No_Press, States if_Reached_Outcome, States if_Continue_Press, States if_Reverse_Press, 
                                    KeyCode move_Left, KeyCode move_Right)
    {
         int temp_Press = Command.check_Axis_(move_Left, move_Right);
        if (temp_Press != 0)
        {
            if (!Check_Same_Direction(last_Axis_Input_, temp_Press))
            {
                if (velocity_ <= 0)
                {
                    return if_Reached_Outcome;
                }
                velocity_ -= deceleration_ * counter_Deceleration_Factor_ * Time.deltaTime;
                transform.position += Vector3.right *  velocity_ * last_Axis_Input_ * Time.deltaTime;
                return if_Reverse_Press;
            }
            return if_Continue_Press;
        }
        return if_No_Press;
    }
    public States Counterceleration(States if_No_Press, States if_Reached_Outcome, States if_Continue_Press, States if_Reverse_Press, 
                                    float modifier, KeyCode move_Left, KeyCode move_Right)
    {
        int temp_Press = Command.check_Axis_(move_Left, move_Right);
        if (temp_Press != 0)
        {
            if (!Check_Same_Direction(last_Axis_Input_, temp_Press))
            {
                if (velocity_ <= 0)
                {
                    return if_Reached_Outcome;
                }
                velocity_ -= deceleration_ * counter_Deceleration_Factor_ * modifier * Time.deltaTime;
                transform.position += Vector3.right *  velocity_ * last_Axis_Input_ * Time.deltaTime;
                return if_Reverse_Press;
            }
            if (velocity_ <= max_Speed_)
                return if_Continue_Press;
        }
        return if_No_Press;
    }
    public States Counterceleration(States if_No_Press, States if_Reached_Outcome, States if_Continue_Press, States if_Reverse_Press,
                                    KeyCode x_minus, KeyCode x_plus, KeyCode y_minus, KeyCode y_plus)
    {
        Vector3 temp = Command.check_Both_DPad_Axes_(x_minus, x_plus, y_minus, y_plus);
        temp = Assign_Axes(temp, first_Axis_, second_Axis_);

        if (temp != Vector3.zero)
        {
            if (temp == last_Temp_Press)
            {
                return if_Continue_Press;
            }

            velocity_ -= (acceleration_ + deceleration_) * Time.deltaTime;
            if (velocity_ <= 0)
            {
                velocity_ = 0;
                return if_Reached_Outcome;
            }
            transform.position += velocity_ * last_Temp_Press * Time.deltaTime;
            return if_Reverse_Press;
        }
        return if_No_Press;
    }
    //Deceleration function for 3D - adaptable pls
} 