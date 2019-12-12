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


    }

    private void Awake()
    {
        Construct_Components();
        Initialize_Components();

    }


    private void Update()
    {
        input_.Update_Keys();

        Handle_States();
        Apply_Inputs();
        Act_Inputs();
        Clear_Inputs();

        Update_Cooldowns();
    }
    
    void Handle_States()
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
                    if(movement_.Gather_Input(key) > 0)
                        continue;
                    break;

            }
            shoot_.Choose_Weapon_State(key);
        }
    }
    void Apply_Inputs()
    {
        current_State_ = movement_.Input_Handler(Player_State.MOVEMENT, Player_State.ROOT);
    }
    void Act_Inputs()
    {
        movement_.Act();
    }
    void Clear_Inputs()
    {
        movement_.Clear();
    }

    void Update_Cooldowns()
    {
        shoot_.Update_Cooldowns();
    }
}