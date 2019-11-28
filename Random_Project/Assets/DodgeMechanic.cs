using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using States = PlayerStates.Player_State;

public class DodgeMechanic : PlayerController
{
    public bool in_Dodge_ = false;
    public Vector3 origin_Pos_ = Vector3.zero;
    public float range_;
    public Vector3 speed_;
    public int dodge_Direction_;
    public float dodge_Cooldown_;
    public float dodge_Cooldown_Max_; //Implement cooldown and input check
    public MovementMechanic movement_;

    void Awake()
    {
        movement_ = GetComponent<MovementMechanic>();
    }

    void Update()
    {
        if (dodge_Cooldown_ != 0)
        {
            dodge_Cooldown_ -= Time.deltaTime;
            if (dodge_Cooldown_ < 0)
                dodge_Cooldown_ = 0;
        }
    }

    public States Enter_Dodge(States if_No_Press, States if_Press, States reset, KeyCode dodge_Left, KeyCode dodge_Right)
    {
        int temp_Press = Command.check_Axis_(dodge_Left, dodge_Right);
        //Enter Dodge
        if (!in_Dodge_)
        {
            if (temp_Press != 0 && dodge_Cooldown_ <= 0)
            {
                origin_Pos_ = transform.position;
                in_Dodge_ = true;
                dodge_Direction_ = temp_Press;
                print("testc");
                return if_Press;
            }
            return if_No_Press;
        }
        return reset;
    }

    //Double tap
    public States Enter_Dodge(States if_No_Press, States if_Press, States reset, KeyCode dodge_Left, KeyCode dodge_Right, KeyCode prev_Dodge_Left, KeyCode prev_Dodge_Right)
    {
        int temp_Press = Command.check_Axis_(dodge_Left, dodge_Right, prev_Dodge_Left, prev_Dodge_Right);
        //Enter Dodge
        if (!in_Dodge_)
        {
            if (temp_Press != 0 && dodge_Cooldown_ <= 0)
            {
                origin_Pos_ = transform.position;
                in_Dodge_ = true;
                dodge_Direction_ = temp_Press;
                print("testc");
                return if_Press;
            }
            return if_No_Press;
        }
        return reset;
    }

    public States Dodge(States if_No_Press, States if_Press, States reset, KeyCode dodge_Left, KeyCode dodge_Right)
    {
        if (in_Dodge_)
        {
            //In Dodge - After entering the dodge, the states "swap" and button presses become irrelevant
            movement_.Translate(speed_, dodge_Direction_);
            if (Vector3.Distance(origin_Pos_, transform.position) < range_)
                return if_No_Press;
            in_Dodge_ = false;
            origin_Pos_ = Vector3.zero;
            dodge_Cooldown_ = dodge_Cooldown_Max_;
            print("test");
            return if_Press;
        }
        return reset;
    }
}
