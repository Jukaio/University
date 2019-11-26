using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

using States = PlayerStates.Player_State;

public class PlayerController : MonoBehaviour
{
    public States state_;

    [HideInInspector] public KeyCode move_Left_;
    [HideInInspector] public KeyCode move_Right_;
    [HideInInspector] public KeyCode dodge_Left_;
    [HideInInspector] public KeyCode dodge_Right_;
    [HideInInspector] public KeyCode shoot_;

    [HideInInspector] public KeyCode weapon_Slot_1_;
    [HideInInspector] public KeyCode weapon_Slot_2_;
    [HideInInspector] public KeyCode weapon_Slot_3_;

    public Text text;

    List<KeyCode> previous_Inputs_;

    public ControlLayout control_Layout;
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
        Set_Buttons();
        Set_Component_Parameters();
    }

    void Set_Buttons()
    {
        move_Left_ = control_Layout.move_Left_;
        move_Right_ = control_Layout.move_Right_;
        dodge_Left_ = control_Layout.dodge_Left_;
        dodge_Right_ = control_Layout.dodge_Right_;
        shoot_ = control_Layout.shoot_;

        weapon_Slot_1_ = control_Layout.weapon_Slot_1_;
        weapon_Slot_2_ = control_Layout.weapon_Slot_2_;
        weapon_Slot_3_ = control_Layout.weapon_Slot_3_;
    }


    void Get_Components()
    {
        control_Layout = GetComponent<ControlLayout>();
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
        shooting_Mechanic_.Choose_Weapon();
        shooting_Mechanic_.Shooting_Mechanic();

        text.text = state_.ToString();

    }


    //////////////////////////////
    //// Player State Machine ////
    //////////////////////////////
    void Update_States()
    {
        switch (state_)
        {
            case States.IDLE:
                Root_State();
                break;

            case States.ACCELERATION:
                Accelerate_State();
                break;

            case States.MAX_SPEED:
                Max_Speed_State();
                break;

            case States.DECELERATION:
                Decelerate_State();
                break;

            case States.COUNTERCELERATION:
                Countercelerate_State();
                break;


            default:
                break;
        }
    }


    /////////////////////
    //// Root State  ////
    /////////////////////

    //Idle
    void Root_State()
    {
        state_ = movement_Mechanic_.Enter_Accerlation(state_, States.ACCELERATION, move_Left_, move_Right_);
    }


    //////////////////////////
    //// Movement States  ////
    //////////////////////////

    //Acceleration
    void Accelerate_State()
    {
        state_ = movement_Mechanic_.Acceleration(state_, States.MAX_SPEED, States.DECELERATION, 
                                                 States.COUNTERCELERATION, move_Left_, move_Right_);
    }
    
    //Max Speed
    void Max_Speed_State()
    {
        state_ = movement_Mechanic_.High_Speed(state_, States.DECELERATION, 
                                               States.COUNTERCELERATION, move_Left_, move_Right_);

    }

    //Deceleration
    void Decelerate_State()
    {
        state_ = movement_Mechanic_.Deceleration(state_, States.IDLE, States.ACCELERATION, 
                                                 States.COUNTERCELERATION, move_Left_, move_Right_);

    }

    //Counterceleration
    void Countercelerate_State()
    {
        state_ = movement_Mechanic_.Counterceleration(state_, States.IDLE, States.DECELERATION, 
                                                      States.ACCELERATION, move_Left_, move_Right_);
    }

    //////////////////////
    //// Dodge State  ////
    //////////////////////

    //General Dodge
    void Dodge_Left_State()
    {
    }
    void Dodge_Right_State()
    {

    }

    // *END OF PLAYER STATE MACHINE

    // *END OF UPDATE AND INPUT HANDLING!
}