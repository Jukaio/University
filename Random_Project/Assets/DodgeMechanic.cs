using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using States = PlayerStates.Player_State;

public class DodgeMechanic : MovementMechanic
{
    public bool dodge_Done_;
    public Vector3 distance_Travelled = Vector3.zero;
    public float range_;
    public float speed_;
    public float dodge_Cooldown_;
    public float dodge_Cooldown_Max_; //Implement cooldown and input check

    public MovementMechanic movement_;
    public Vector3 tempPos;



    //void Awake()
    //{
    //    movement_ = GetComponent<MovementMechanic>();
    //}

    //void Update()
    //{
    //    if (dodge_Cooldown_ != 0)
    //    {
    //        dodge_Cooldown_ -= Time.deltaTime;
    //        if (dodge_Cooldown_ < 0)
    //            dodge_Cooldown_ = 0;
    //    }
    //}

    //public States Enter_Dodge(States current_state)
    //{
    //    if (dodge_Cooldown_ <= 0)
    //    {
    //        if (Input.GetKey(KeyCode.Q))
    //        {
    //            tempPos = transform.position;
    //            distance_Travelled = Vector3.zero;
    //            dodge_Cooldown_ = dodge_Cooldown_Max_;
    //            return States.DODGE_LEFT;
    //        }
    //        else if (Input.GetKey(KeyCode.E))
    //        {
    //            tempPos = transform.position;
    //            distance_Travelled = Vector3.zero;
    //            dodge_Cooldown_ = dodge_Cooldown_Max_;
    //            return States.DODGE_RIGHT;
    //        }
    //    }

    //    return current_state;
    //}


    //public States Dodge(int direction, States state)
    //{
    //    distance_Travelled = transform.position - tempPos;
    //    if (distance_Travelled.magnitude >= range_)
    //    {
    //        int temp = (int)States.DECELERATE_RIGHT * direction / Mathf.Abs(direction);
    //        return movement_.Enter_Deceleration((States) temp , KeyCode.None, KeyCode.None, direction);
    //    }
    //    return movement_.Accelerate(state, KeyCode.None, direction);

    //}
}
