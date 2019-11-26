using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    public PlayerStates.Player_State state_;

    public MovementMechanic movement_Mechanic_;
    public ShootingMechanic shooting_Mechanic_;
    public DodgeMechanic dodge_Mechanic_;

    ////////////////////////////////////////////
    ////////////////////////////////////////////
    ///////// Start and Initialization /////////
    ////////////////////////////////////////////
    ////////////////////////////////////////////

    void Start()
    {

        Get_Components();
        Set_Component_Parameters();
    }

    void Get_Components()
    {
        shooting_Mechanic_ = GetComponent<ShootingMechanic>();
        movement_Mechanic_ = GetComponent<MovementMechanic>();
        dodge_Mechanic_ = GetComponent<DodgeMechanic>();
    }

    void Set_Component_Parameters()
    {
    
    }

    
    /////////////////////////////////////////////
    /////////////////////////////////////////////
    ///////// Update and Input Handling /////////
    /////////////////////////////////////////////
    /////////////////////////////////////////////

    void Update()
    {
        Update_States();

        state_ = (PlayerStates.Player_State) dodge_Mechanic_.Enter_Dodge(state_);
        shooting_Mechanic_.Choose_Weapon();
        shooting_Mechanic_.Shooting_Mechanic();
    }


    //////////////////////////////
    //// Player State Machine ////
    //////////////////////////////
    void Update_States()
    {
        switch (state_)
        {
            case PlayerStates.Player_State.IDLE:
                Idle_State();
                break;

            case PlayerStates.Player_State.ACCELERATE_LEFT:
                Accelerate_Left_State();
                break;

            case PlayerStates.Player_State.ACCELERATE_RIGHT:
                Accelerate_Right_State();
                break;

            case PlayerStates.Player_State.DECELERATE_LEFT:
                Decelerate_Left_State();
                break;

            case PlayerStates.Player_State.DECELERATE_RIGHT:
                Decelerate_Right_State();
                break;

            case PlayerStates.Player_State.DODGE_LEFT:
                Dodge_Left_State();
                break;

            case PlayerStates.Player_State.DODGE_RIGHT:
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
            state_ = PlayerStates.Player_State.ACCELERATE_LEFT;
        }
        else if (Input.GetKey(KeyCode.D))
        {
            state_ = PlayerStates.Player_State.ACCELERATE_RIGHT;
        }
    }


    //////////////////////////
    //// Movement States  ////
    //////////////////////////

    //Acceleration
    void Accelerate_Left_State()
    {
        state_ = movement_Mechanic_.Accelerate(state_, KeyCode.A, -1);
    }
    void Accelerate_Right_State()
    {
        state_ = movement_Mechanic_.Accelerate(state_, KeyCode.D, 1);
    }

    //Deacceleration
    void Decelerate_Left_State()
    {
        state_ = movement_Mechanic_.Enter_Deceleration(state_, KeyCode.A, KeyCode.D, 1);
    }
    void Decelerate_Right_State()
    {
        state_ = movement_Mechanic_.Enter_Deceleration(state_, KeyCode.D, KeyCode.A, -1);
    }


    //////////////////////
    //// Dodge State  ////
    //////////////////////

    //General Dodge
    void Dodge_Left_State()
    {
        if (dodge_Mechanic_.Dodge(-1))
        {
            state_ = PlayerStates.Player_State.IDLE;
        }
    }
    void Dodge_Right_State()
    {
        if (dodge_Mechanic_.Dodge(1))
        {
            state_ = PlayerStates.Player_State.IDLE;
        }

    }

    // *END OF PLAYER STATE MACHINE

    // *END OF UPDATE AND INPUT HANDLING!
}