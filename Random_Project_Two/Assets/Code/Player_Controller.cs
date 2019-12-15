using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Movement;


using Key = Custom_Input.Key;

//Multi-Accessible Mechanics gather inputs. I.e. D is rightr, A is left, but both at the same time is Nothing.

public class Player_Controller : MonoBehaviour
{
    Root root_;
    Movement_Manager movement_;
    Custom_Input input_;
    Shooting_Mechanic shoot_;

    //Shooting Info
    public GameObject bullet_Template_One_;
    public GameObject bullet_Template_Two_;
    public GameObject bullet_Template_Three_;


    public enum Player_State
    {
        ROOT,
        MOVEMENT,
        FORCE
    }
    public Player_State current_State_;

    private void Construct_Components()
    {
        root_ = new Root();
        input_ = new Custom_Input();

        movement_ = new Movement_Manager(gameObject);
        shoot_ = new Shooting_Mechanic(gameObject);
    }

    private void Initialize_Components()
    {
        movement_.Activate_Axis(input_, 10.0f, 15.0f, new Vector3(1.0f, 0.0f, 0.0f), Key.A, Key.D);
        movement_.Activate_Axis(input_, 10.0f, 15.0f, new Vector3(0.0f, 1.0f, 0.0f), Key.S, Key.W);

        shoot_.Activate_Shooting(Key.Space);
        shoot_.Activate_Weapon_One(Key.One, 50.0f, 7.0f, 0.2f);
        shoot_.Activate_Weapon_Two(Key.Two, 50.0f, 5.0f, 1.0f, 0.35f);
        shoot_.Activate_Weapon_Three(Key.Three, 50.0f, 10.0f, 35.0f, 0.3f);

        shoot_.Init_Bullet_Clip(64, Shooting_Mechanic.Weapon_Type.NORMAL, bullet_Template_One_);
        shoot_.Init_Bullet_Clip(128, Shooting_Mechanic.Weapon_Type.TRIPLE, bullet_Template_Two_);
        shoot_.Init_Bullet_Clip(128, Shooting_Mechanic.Weapon_Type.TRIPLE_SPLIT, bullet_Template_Three_);
    }

    private void Awake()
    {
        Construct_Components();
        Initialize_Components();
    }


    private void Update()
    {
        input_.Update_Keys();

        Handle_Inputs();
        Apply_Inputs();
        Act_Inputs();
        Clear_Inputs();

    }
    
    void Handle_Inputs()
    {
        while (input_.input_Queue_.Count > 0)
        {
            Key key = input_.input_Queue_.Dequeue();
        Here:
            switch (current_State_)
            {
                case Player_State.ROOT: // Root State
                    current_State_ = root_.Input_Handler(gameObject, Player_State.ROOT, Player_State.MOVEMENT, key);
                    if (current_State_ != Player_State.ROOT)
                        goto Here;
                    break;

                case Player_State.MOVEMENT: // Movement State
                    if (movement_.Gather_Input(key) > 0)
                        break;
                    break;

            }
            shoot_.Choose_Weapon_State(key);
            shoot_.Gather_Input(key);
        }
    }

    void Apply_Inputs()
    {
        current_State_ = movement_.Input_Handler(Player_State.MOVEMENT, Player_State.ROOT);
    }
    void Act_Inputs()
    {
        movement_.Act();
        shoot_.Act();
    }
    void Clear_Inputs()
    {
        movement_.Clear();
        shoot_.Clear();
    }
}