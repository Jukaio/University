using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using States = PlayerStates.Player_State;

public class PlayerController : MonoBehaviour
{
    public States state_;

    [HideInInspector] public KeyCode move_Left_;
    [HideInInspector] public KeyCode move_Right_;
    [HideInInspector] public KeyCode dodge_Left_;
    [HideInInspector] public KeyCode dodge_Right_;
    [HideInInspector] public KeyCode move_Left_3D_;
    [HideInInspector] public KeyCode move_Right_3D_;
    [HideInInspector] public KeyCode move_Down_3D_;
    [HideInInspector] public KeyCode move_Up_3D_;
    [HideInInspector] public KeyCode shoot_;

    [HideInInspector] public KeyCode weapon_Slot_1_;
    [HideInInspector] public KeyCode weapon_Slot_2_;
    [HideInInspector] public KeyCode weapon_Slot_3_;

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

        move_Left_3D_ = control_Layout.move_Left_3D_;
        move_Right_3D_ = control_Layout.move_Right_3D_;
        move_Down_3D_ = control_Layout.move_Down_3D_;
        move_Up_3D_ = control_Layout.move_Up_3D_;

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
        shooting_Mechanic_.Choose_Weapon(weapon_Slot_1_, weapon_Slot_2_,weapon_Slot_3_);
        shooting_Mechanic_.Shooting_Mechanic(shoot_);
        state_ = dodge_Mechanic_.Enter_Dodge(state_, States.DODGE, state_, dodge_Left_, dodge_Right_);
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

            case States.DODGE:
                Dodge_State();
                break;

            case States.DODGE_DECELERATION:
                Dodge_Deceleration_State();
                break;

            case States.DODGE_COUNTERCELERATION:
                Dodge_Counterceleration_State();
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
        state_ = movement_Mechanic_.Acceleration(States.IDLE, States.MAX_SPEED, States.ACCELERATION,
                                                 move_Left_, move_Right_);
        state_ = movement_Mechanic_.Acceleration(States.IDLE, States.MAX_SPEED, States.ACCELERATION, States.COUNTERCELERATION, move_Left_3D_, move_Right_3D_, move_Down_3D_, move_Up_3D_);
    }


    //////////////////////////
    //// Movement States  ////
    //////////////////////////

    //Acceleration
    void Accelerate_State()
    {
        //state_ = movement_Mechanic_.Acceleration(States.DECELERATION, States.MAX_SPEED, States.ACCELERATION,
        //                                         move_Left_, move_Right_);
        state_ = movement_Mechanic_.Acceleration(States.DECELERATION, States.MAX_SPEED, States.ACCELERATION, States.COUNTERCELERATION, move_Left_3D_, move_Right_3D_, move_Down_3D_, move_Up_3D_);
    }

    //Max Speed
    void Max_Speed_State()
    {
        //state_ = movement_Mechanic_.High_Speed(States.DECELERATION, States.COUNTERCELERATION,
        //                                       States.MAX_SPEED, move_Left_, move_Right_);
        state_ = movement_Mechanic_.High_Speed(States.DECELERATION, States.COUNTERCELERATION, States.MAX_SPEED,
                                               move_Left_3D_, move_Right_3D_, move_Down_3D_, move_Up_3D_);
    }

    //Deceleration
    void Decelerate_State()
    {
        //state_ = movement_Mechanic_.Deceleration(States.DECELERATION, States.IDLE, States.ACCELERATION,
        //                                         States.COUNTERCELERATION, move_Left_, move_Right_);
        state_ = movement_Mechanic_.Deceleration(States.DECELERATION, States.IDLE, States.ACCELERATION, States.COUNTERCELERATION, 
                                                 move_Left_3D_, move_Right_3D_, move_Down_3D_, move_Up_3D_);

    }

    //Counterceleration
    void Countercelerate_State()
    {
        //state_ = movement_Mechanic_.Counterceleration(States.DECELERATION, States.IDLE, States.ACCELERATION,
        //                                              States.COUNTERCELERATION, move_Left_, move_Right_);
        state_ = movement_Mechanic_.Counterceleration(States.DECELERATION, States.IDLE, States.ACCELERATION, States.COUNTERCELERATION,
                                                      move_Left_3D_, move_Right_3D_, move_Down_3D_, move_Up_3D_);
    }


    //////////////////////
    //// Dodge State  ////
    //////////////////////

    //General Dodge
    void Dodge_State()
    {
        state_ = dodge_Mechanic_.Dodge(States.DODGE, States.DODGE_DECELERATION, States.IDLE, dodge_Left_, dodge_Right_);
    }

    void Dodge_Deceleration_State()
    {
        state_ = dodge_Mechanic_.Deceleration(States.DODGE_DECELERATION, States.IDLE,
                                                 States.ACCELERATION, States.DODGE_COUNTERCELERATION, move_Left_, move_Right_);
    }

    void Dodge_Counterceleration_State()
    {
        state_ = dodge_Mechanic_.Counterceleration(States.DODGE_DECELERATION, States.IDLE,
                                                      States.ACCELERATION, States.DODGE_COUNTERCELERATION, move_Left_, move_Right_);
    }


    // *END OF PLAYER STATE MACHINE

    // *END OF UPDATE AND INPUT HANDLING!
}