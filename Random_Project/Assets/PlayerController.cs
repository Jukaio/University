using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    public enum Player_State
    {
        DEACCELERATE_LEFT = -2,
        ACCELERATE_LEFT = -1,
        IDLE = 0,
        ACCELERATE_RIGHT,
        DEACCELERATE_RIGHT,
        DODGE_LEFT,
        DODGE_RIGHT
    }
    public Player_State state_;

    public MovementMechanic movement_Mechanic_;
    public ShootingMechanic shooting_Mechanic_;

    ////////////////////////////////////////////
    ////////////////////////////////////////////
    ///////// Start and Initialization /////////
    ////////////////////////////////////////////
    ////////////////////////////////////////////

    void Start()
    {
        Get_Components();
    }

    void Get_Components()
    {
        shooting_Mechanic_ = GetComponent<ShootingMechanic>();
        movement_Mechanic_ = GetComponent<MovementMechanic>();
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
    }


    //////////////////////////////
    //// Player State Machine ////
    //////////////////////////////
    void Update_States()
    {
        switch (state_)
        {
            case Player_State.IDLE:
                Idle_State();
                break;

            case Player_State.ACCELERATE_LEFT:
                Accelerate_Left_State();
                break;

            case Player_State.ACCELERATE_RIGHT:
                Accelerate_Right_State();
                break;

            case Player_State.DEACCELERATE_LEFT:
                Deaccel_Left_State();
                break;

            case Player_State.DEACCELERATE_RIGHT:
                Deaccel_Right_State();
                break;

            case Player_State.DODGE_LEFT:
                Dodge_Left_State();
                break;

            case Player_State.DODGE_RIGHT:
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
            state_ = Player_State.ACCELERATE_LEFT;
        }
        else if (Input.GetKey(KeyCode.D))
        {
            state_ = Player_State.ACCELERATE_RIGHT;
        }
    }


    //////////////////////////
    //// Movement States  ////
    //////////////////////////

    //Acceleration
    void Accelerate_Left_State()
    {
        movement_Mechanic_.Accelerate(-1);
        if (!Input.GetKey(KeyCode.A))
        {
            state_ = Player_State.DEACCELERATE_LEFT;
        }
    }
    void Accelerate_Right_State()
    { 
        movement_Mechanic_.Accelerate(1);
        if (!Input.GetKey(KeyCode.D))
        {
            state_ = Player_State.DEACCELERATE_RIGHT;
        }
    }

    //Deacceleration
    void Deaccel_Left_State()
    {
        if (Input.GetKey(KeyCode.A))
        {
            state_ = Player_State.ACCELERATE_LEFT;
            return;
        }
        else if (Input.GetKey(KeyCode.D))
        {
            if (movement_Mechanic_.Counter_Accelerate(1))
                state_ = Player_State.IDLE;
            return;
        }
        else if (movement_Mechanic_.Deaccelerate(1))
            state_ = Player_State.IDLE;
    }
    void Deaccel_Right_State()
    {
        if (Input.GetKey(KeyCode.D))
        {
            state_ = Player_State.ACCELERATE_RIGHT;
            return;
        }
        else if (Input.GetKey(KeyCode.A))
        {
            if (movement_Mechanic_.Counter_Accelerate(-1))
                state_ = Player_State.IDLE;
            return;
        }
        else if (movement_Mechanic_.Deaccelerate(-1))
            state_ = Player_State.IDLE;
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
                state_ = Player_State.DODGE_LEFT;
            }
            else if (Input.GetKey(KeyCode.E))
            {
                state_ = Player_State.DODGE_RIGHT;
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
            state_ = Player_State.IDLE;
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
            state_ = Player_State.IDLE;
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