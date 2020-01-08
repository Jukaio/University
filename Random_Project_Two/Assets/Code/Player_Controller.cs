using UnityEngine;
using Weapons;

using Key = Custom_Input.Key;

//Multi-Accessible Mechanics gather inputs. I.e. D is rightr, A is left, but both at the same time is Nothing.

public class Player_Controller : MonoBehaviour
{
    Movement movement_;
    Rigidbody rigid_Body_;

    Custom_Input input_;
    Weapon_Manager weapon_Manager_;

    //Shooting Info
    public GameObject bullet_Template_;

    AudioSource weapon_Audio_Source;
    public AudioClip[] weapon_Audio_Clips;

    public enum Player_State
    {
        IDLE,
        MOVEMENT,
        FORCE
    }
    public Player_State current_State_;
    public Player_State previous_State_;
    

    private void Construct_Components()
    {
        weapon_Audio_Source = gameObject.AddComponent<AudioSource>();

        movement_ = gameObject.AddComponent<Movement>();

        input_ = new Custom_Input();

        weapon_Manager_ = new Weapon_Manager(gameObject, weapon_Audio_Source, weapon_Audio_Clips);
    }

    private void Initialize_Components()
    {
        //
        rigid_Body_ = GetComponent<Rigidbody>();

        //Create the Weapon
        weapon_Manager_.Create_Weapon(Key.Space, 0.22f);
        weapon_Manager_.Create_Weapon(Key.Space, 0.35f);
        weapon_Manager_.Create_Weapon(Key.Space, 0.4f);

        //Create Components
        weapon_Manager_.Create_Weapon_Component(bullet_Template_, 24, Vector3.zero, 12.0f, new Vector3(-1.1f, 0.0f, 0.0f), 10.0f, Vector3.forward);
        weapon_Manager_.Create_Weapon_Component(bullet_Template_, 24, Vector3.zero, 12.0f, new Vector3(0.0f, 0.0f, 0.4f), 10.0f, Vector3.forward);
        weapon_Manager_.Create_Weapon_Component(bullet_Template_, 24, Vector3.zero, 12.0f, new Vector3(1.1f, 0.0f, 0.0f), 10.0f, Vector3.forward);
        
        //Add Components to the Weapon
        weapon_Manager_.Construct_Weapon(0, 1);
        weapon_Manager_.Construct_Weapon(1, 0, 2);
    }

    private void Awake()
    {
        Construct_Components();
        Initialize_Components();
    }


    private void Update()
    {
        input_.Update_Keys();

        Input_Handler();
        State_Handler();

    }

    ///  ///  ///  ///  ///  ///
    ///  Bundles All Inputs  ///
    ///  ///  ///  ///  ///  ///
    void Input_Handler()
    {
        while (input_.input_Queue_.Count > 0)
        {
            previous_State_ = current_State_;

            Key key = input_.input_Queue_.Dequeue();

        Check_Input:
            switch (current_State_)
            {
                case Player_State.IDLE: // Root State
                    current_State_ = Handle_Idle_Inputs(key);
                    if (previous_State_ != current_State_)
                        goto Check_Input;
                    break;

                case Player_State.MOVEMENT: // Movement State
                    movement_.Handle_Input(key, Handle_Movement_Inputs);
                    break;
            }
            Handle_Shooting_Inputs(key);
        }
    }

    Player_State Handle_Idle_Inputs(Key key)
    {
        switch (key)
        {
            case Key.NONE:
                return Player_State.IDLE;

            case Key.A:
            case Key.D:
            case Key.S:
            case Key.W:
                return Player_State.MOVEMENT;

            default:
                return Player_State.IDLE;
        }
    }

    ///  ///  ///  ///
    ///  Movement  ///
    ///  ///  ///  ///
    ///  // Handles Input
    enum Movement_States
    {
        IDLE,
        ACCEL,
        DECEL,
    }
    Movement_States movement_States_;
    Vector3 input_Vector_ = Vector3.zero;
    Vector3 velocity_ = Vector3.zero;
    void Handle_Movement_Inputs(Key key)
    {
        switch (key)
        {
            case Key.A:
                //Add Acceleration to Velocity.x
                input_Vector_ += Vector3.left;
                break;

            case Key.D:
                //Subtract Acceleration to Velocity.x
                input_Vector_ += Vector3.right;
                break;

            case Key.S:
                //Subtract Acceleration to Velocity.y
                
                break;

            case Key.W:
                //Add Acceleration to Velocity.y
                break;

            default:
                break;
        }
    }
    ///  //Handles States (If Input happened)
    void Handle_Movement_States()
    {
        switch (movement_States_)
        {
            case Movement_States.IDLE:
                
                switch(input_Vector_.x)
                {
                    case 0:

                        break;

                    default:
                        movement_States_ = Movement_States.ACCEL;
                        break;
                }

                break;

            case Movement_States.ACCEL:

                break;

            case Movement_States.DECEL:

                break;
        }

        rigid_Body_.velocity = velocity_;

        input_Vector_ = Vector3.zero;
    }

    ///  ///  ///  ///
    ///  Shooting  ///
    ///  ///  ///  ///
    ///  // Handles Input
    void Handle_Shooting_Inputs(Key key)
    {
        switch (key)
        {
            case Key.NONE:
                break;

            case Key.One:
                weapon_Manager_.Change_Weapon(0);
                break;

            case Key.Two:
                weapon_Manager_.Change_Weapon(1);
                break;

            case Key.Three:
                weapon_Manager_.Change_Weapon(2);
                break;

            case Key.Space:
                weapon_Manager_.Push_Shoot_Weapon();
                break;

            default:
                break;
        }
    }
    ///  //Handles States (If Input happened)
    void Handle_Shooting_States()
    {
        weapon_Manager_.Handle_Weapon_Change_Cooldown();
        weapon_Manager_.Handle_State();
    }



    ///  ///  ///  ///  ///  ///
    ///  Bundles All States  ///
    ///  ///  ///  ///  ///  ///
    void State_Handler()
    {
        Handle_Movement_States();
        Handle_Shooting_States();
    }
}