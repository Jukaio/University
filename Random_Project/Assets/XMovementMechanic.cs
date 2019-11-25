using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class XMovementMechanic : MonoBehaviour
{
    //////////////////////////
    //// Movement States  ////
    //////////////////////////

    void Init_Movement_Data()
    {
        if (counter_Deaccel_Factor_ == 0)
        {
            counter_Deaccel_Factor_ = 1;
        }
    }

    //Modifiable Data
    public Vector3 acceleration_;
    public Vector3 deacceleration_;
    public float counter_Deaccel_Factor_;
    public float max_Speed_;

    //Data
    public Vector3 velocity_;

    //Acceleration
    SingletonObjectStates.Player_State Accelerate_Left_State()
    {
        velocity_ += acceleration_;
        transform.position -= velocity_;
        if (!Input.GetKey(KeyCode.A))
        {
            return SingletonObjectStates.Player_State.DEACCELERATE_LEFT;
        }
        return SingletonObjectStates.Player_State.ACCELERATE_LEFT;
    }

    void Accelerate_Right_State()
    {
        velocity_ += acceleration_;
        transform.position += velocity_;
        if (!Input.GetKey(KeyCode.D))
        {
            state_ = SingletonObjectStates.Player_State.DEACCELERATE_RIGHT;
        }
    }

    //Deacceleration
    void Deaccel_Left_State()
    {
        if (velocity_.x > 0 && !Input.GetKey(KeyCode.A) && !Input.GetKey(KeyCode.D))
        {
            velocity_ -= deacceleration_;
            transform.position -= velocity_;
        }
        else if (Input.GetKey(KeyCode.A))
        {
            state_ = SingletonObjectStates.Player_State.ACCELERATE_LEFT;
        }
        else if (Input.GetKey(KeyCode.D))
        {
            if (velocity_.x > 0)
            {
                velocity_ -= deacceleration_ * counter_Deaccel_Factor_;
                transform.position -= velocity_;
            }
            else
                state_ = SingletonObjectStates.Player_State.ACCELERATE_RIGHT;

        }
        else
        {
            velocity_ = Vector3.zero;
            state_ = SingletonObjectStates.Player_State.IDLE;
        }
    }
    void Deaccel_Right_State()
    {
        if (velocity_.x > 0 && !Input.GetKey(KeyCode.D) && !Input.GetKey(KeyCode.A))
        {
            velocity_ -= deacceleration_;
            transform.position += velocity_;
        }
        else if (Input.GetKey(KeyCode.D))
        {
            state_ = SingletonObjectStates.Player_State.ACCELERATE_RIGHT;
        }
        else if (Input.GetKey(KeyCode.A))
        {
            if (velocity_.x > 0)
            {
                velocity_ -= deacceleration_ * counter_Deaccel_Factor_;
                transform.position += velocity_;
            }
            else
                state_ = SingletonObjectStates.Player_State.ACCELERATE_LEFT;
        }
        else
        {
            velocity_ = Vector3.zero;
            state_ = SingletonObjectStates.Player_State.IDLE;
        }
    }


}
