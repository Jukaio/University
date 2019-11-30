using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using States = PlayerStates.Player_State;

public class DodgeMechanic : MonoBehaviour
{
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


    /////////////////////////////////
    //// Dodge and Configuration ////
    /////////////////////////////////

    //Modifiable Data
    [SerializeField] private float range_;
    [SerializeField] private float speed_;
    [SerializeField] private float deceleration_Factor_;
    [SerializeField] private float counterceleration_Factor_;
    [SerializeField] private float dodge_Cooldown_Max_; 

    //Data
    private bool in_Dodge_ = false;
    private Vector3 origin_Pos_ = Vector3.zero;
    private int dodge_Direction_;
    private float dodge_Cooldown_;
    private MovementMechanic movement_;

    //Enter Dodge
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

    //Dodge (Quick Movement)
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
            return if_Press;
        }
        return reset;
    }

    //Deceleration after Dodge
    public States Deceleration(States if_No_Press, States if_Reached_Outcome, States if_Continue_Press, States if_Reverse_Press, KeyCode move_Left, KeyCode move_Right)
    {
        return movement_.Deceleration(if_No_Press, if_Reached_Outcome, if_Continue_Press, 
                                      if_Reverse_Press, deceleration_Factor_, move_Left, move_Right);
    }

    //Counterceleration during Deceleration of Dodge
    public States Counterceleration(States if_No_Press, States if_Reached_Outcome, States if_Continue_Press, States if_Reverse_Press, KeyCode move_Left, KeyCode move_Right)
    {
        return movement_.Counterceleration(if_No_Press, if_Reached_Outcome, if_Continue_Press, 
                                           if_Reverse_Press, counterceleration_Factor_, move_Left, move_Right);
    }
}
