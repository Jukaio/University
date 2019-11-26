using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class DodgeMechanic : MonoBehaviour
{
    public bool dodge_Done_;
    Vector3 distance_Travelled = Vector3.zero;
    public float range_;
    public float speed_;
    public float dodge_Cooldown_;
    public float dodge_Cooldown_Max_; //Implement cooldown and input check


    public PlayerStates.Player_State Enter_Dodge(PlayerStates.Player_State current_state)
    {
        if (dodge_Cooldown_ <= 0)
        {
            if (Input.GetKey(KeyCode.Q))
            {
                return PlayerStates.Player_State.DODGE_LEFT;
            }
            else if (Input.GetKey(KeyCode.E))
            {
                return PlayerStates.Player_State.DODGE_RIGHT;
            }
        }

        return current_state;
    }


    public PlayerStates.Player_State Dodge(int direction, PlayerStates.Player_State state)
    {
        if (distance_Travelled.magnitude >= range_)
        {
            distance_Travelled = Vector3.zero;
            return state;
        }
        transform.position += new Vector3(speed_, 0, 0) * direction;
        distance_Travelled += new Vector3(speed_, 0, 0) * direction;
        return PlayerStates.Player_State.IDLE;

    }
}
