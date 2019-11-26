using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovementMechanic : MonoBehaviour
{
    public Vector3 velocity_;
    [SerializeField] private Vector3 acceleration_;
    [SerializeField] private float counter_Deceleration_Factor_;
    [SerializeField] private Vector3 deceleration_;
    [SerializeField] private float max_Speed_x_;

    public PlayerStates.Player_State Enter_Acceleration(PlayerStates.Player_State current_state)
    {
        if (Input.GetKey(KeyCode.A))
        {
            return PlayerStates.Player_State.ACCELERATE_LEFT;
        }
        else if (Input.GetKey(KeyCode.D))
        {
            return PlayerStates.Player_State.ACCELERATE_RIGHT;
        }
        return current_state;
    }


    void Awake()
    {
        Init_Default();
    }

    void Update()
    {
        Correction();
    }

    void Init_Default()
    {
        if (counter_Deceleration_Factor_ == 0)
        {
            counter_Deceleration_Factor_ = 1;
        }

    }

    void Correction()
    {
        if (velocity_.x > max_Speed_x_)
            velocity_.x = max_Speed_x_;
    }

    public PlayerStates.Player_State Accelerate(PlayerStates.Player_State current_state, KeyCode keyCode,int direction)
    {
        velocity_ += acceleration_;
        transform.position += velocity_ * direction;
        if (!Input.GetKey(keyCode))
            return current_state + direction;
        return current_state;
    }

    public PlayerStates.Player_State Enter_Deceleration(PlayerStates.Player_State state, KeyCode accel, KeyCode counter, int direction)
    {
        if (Input.GetKey(accel))
        {
            return PlayerStates.Player_State.ACCELERATE_LEFT;
        }
        else if (Input.GetKey(counter))
        {
            if (Counter_Accelerate(direction))
                return PlayerStates.Player_State.IDLE;
            return state;
        }
        else if (Decelerate(direction))
            return PlayerStates.Player_State.IDLE;
        return state;
    }

    public bool Decelerate(int direction)
    {
        if (velocity_.x >= 0)
        {
            velocity_ -= deceleration_;
            transform.position -= velocity_ * direction;
            return false;
        }
        velocity_ = Vector3.zero;
        return true;

    }

    public bool Counter_Accelerate(int direction)
    {
        if (velocity_.x >= 0)
        {
            velocity_ -= deceleration_ * counter_Deceleration_Factor_;
            transform.position -= velocity_ * direction;
            return false;
        }
        velocity_ = Vector3.zero;
        return true;
    }
}