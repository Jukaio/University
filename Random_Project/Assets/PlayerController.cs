using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    public SingletonObjectStates.Player_State state_;

    public XMovementMechanic x_Movement_;
    public ShootingMechanic shooting_Mechanic_;

    ////////////////////////////////////////////
    ////////////////////////////////////////////
    ///////// Start and Initialization /////////
    ////////////////////////////////////////////
    ////////////////////////////////////////////

    void Start()
    {
        Get_Components();
        Init_Movement_Data();
    }

    void Get_Components()
    {
        shooting_Mechanic_ = GetComponent<ShootingMechanic>();
        x_Movement_ = GetComponent<XMovementMechanic>();
    }
    /////////////////////////////////////////////
    /////////////////////////////////////////////
    ///////// Update and Input Handling /////////
    /////////////////////////////////////////////
    /////////////////////////////////////////////

    void Update()
    {
        Update_States();

        Dodge_Mechanic();
        shooting_Mechanic_.Choose_Weapon();
        shooting_Mechanic_.Shooting_Mechanic();
        Update_Cooldowns();
        if (velocity_.x > +max_Speed_)
        {
            velocity_.x = max_Speed_;
        }
    }


    //////////////////////////////
    //// Player State Machine ////
    //////////////////////////////
    void Update_States()
    {
        switch (state_)
        {
            case SingletonObjectStates.Player_State.IDLE:
                Idle_State();
                break;

            case SingletonObjectStates.Player_State.ACCELERATE_LEFT:
                Accelerate_Left_State();
                break;

            case SingletonObjectStates.Player_State.ACCELERATE_RIGHT:
                Accelerate_Right_State();
                break;

            case SingletonObjectStates.Player_State.DEACCELERATE_LEFT:
                Deaccel_Left_State();
                break;

            case SingletonObjectStates.Player_State.DEACCELERATE_RIGHT:
                Deaccel_Right_State();
                break;

            case SingletonObjectStates.Player_State.DODGE_LEFT:
                Dodge_Left_State();
                break;

            case SingletonObjectStates.Player_State.DODGE_RIGHT:
                Dodge_Right_State();
                break;

            default:
                break;
        }
    }


    /////////////////////
    //// Root State  ////
    /////////////////////

    //Idle
    void Idle_State()
    {
        if (Input.GetKey(KeyCode.A) &&
                    Input.GetKey(KeyCode.D))
        {

        }
        else if (Input.GetKey(KeyCode.A))
        {
            state_ = SingletonObjectStates.Player_State.ACCELERATE_LEFT;
        }
        else if (Input.GetKey(KeyCode.D))
        {
            state_ = SingletonObjectStates.Player_State.ACCELERATE_RIGHT;
        }
    }


    //////////////////////////
    //// Movement States  ////
    //////////////////////////

    void Init_Movement_Data()
    {
        if(counter_Deaccel_Factor_ == 0)
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
    void Accelerate_Left_State()
    {
        velocity_ += acceleration_;
        transform.position -= velocity_;
        if (!Input.GetKey(KeyCode.A))
        {
            state_ = SingletonObjectStates.Player_State.DEACCELERATE_LEFT;
        }
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
        else if(Input.GetKey(KeyCode.A))
        {
            state_ = SingletonObjectStates.Player_State.ACCELERATE_LEFT;
        }
        else if(Input.GetKey(KeyCode.D))
        {
            if(velocity_.x > 0)
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


    //////////////////////
    //// Dodge State  ////
    //////////////////////

    //Modifiable Data
    public float dodge_Speed_;
    public float dodge_Distance_;
    public float dodge_Cooldown_Max_;

    //Data
    public bool dodge_Done_;
    public float dodge_Cooldown_;
    Vector3 temp_Position_;

    //Check Dodge Input and Conditions
    void Dodge_Mechanic()
    {
        if (dodge_Cooldown_ <= 0)
        {
            if (Input.GetKey(KeyCode.Q))
            {
                state_ = SingletonObjectStates.Player_State.DODGE_LEFT;
            }
            else if (Input.GetKey(KeyCode.E))
            {
                state_ = SingletonObjectStates.Player_State.DODGE_RIGHT;
            }
        }
    }

    //General Dodge
    void Dodge_Left_State()
    {
        if (dodge_Done_)
        {
            temp_Position_ = transform.position; //Init dodge
            dodge_Done_ = false;
            return;
        }

        if (transform.position.x <= temp_Position_.x - dodge_Distance_)
        {
            dodge_Done_ = true;
            state_ = SingletonObjectStates.Player_State.IDLE;
            dodge_Cooldown_ = dodge_Cooldown_Max_;

        }

        transform.position += new Vector3(-dodge_Speed_, 0, 0);
    }
    void Dodge_Right_State()
    {
        if (dodge_Done_)
        {
            temp_Position_ = transform.position; //Init dodge
            dodge_Done_ = false;
            return;
        }

        if (transform.position.x >= temp_Position_.x + dodge_Distance_)
        {
            dodge_Done_ = true;
            state_ = SingletonObjectStates.Player_State.IDLE;
            dodge_Cooldown_ = dodge_Cooldown_Max_;

        }

        transform.position += new Vector3(dodge_Speed_, 0, 0);
    }

    // *END OF PLAYER STATE MACHINE


    //////////////////////////
    //// Update Cooldowns ////
    //////////////////////////
    
    void Update_Cooldowns()
    {
        if (dodge_Cooldown_ != 0)
        {
            dodge_Cooldown_ -= Time.deltaTime;
            if (dodge_Cooldown_ < 0)
                dodge_Cooldown_ = 0;
        }

    }

    // *END OF UPDATE COOLDOWNS


    // *END OF UPDATE AND INPUT HANDLING!
}