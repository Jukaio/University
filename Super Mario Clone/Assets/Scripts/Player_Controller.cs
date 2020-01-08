using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

using Status;

/*
I AM AN IDIOT - MERGE MOVEMENT_RIGHT AND MOVEMENT_LEFT. MAKE IT HAPPEN  
DUE TO THE PREPARATION OF IMPUTS, YOU CAN JUST PUT BOTH IN - BOTH PRESSED WILL NEVER HAPPEN!!
  */

public class Player_Controller : MonoBehaviour
{
    public enum States
    {
        IDLE,
        MOVEMENT_LEFT,
        MOVEMENT_RIGHT,
        JUMP,
        JUMP_LEFT,
        JUMP_RIGHT,
        FALL,
        FALL_LEFT,
        FALL_RIGHT
    }


    public States current_State_;
    public States next_State_;

    static public State[] states_;


    public Input_Manager input_Manager_ = new Input_Manager();

    public List<Button_Names> queued_Inputs_Buffer_;

    SpriteRenderer renderer_;
    Animator animator_;

    public int Add_State(State state)
    {
        int state_ID = states_.Length;
        if (states_.Length == 0)
        {
            states_ = new State[1];
        }
        else
        {
            State[] temp = states_;
            states_ = new State[temp.Length + 1];

            for (int i = 0; i < temp.Length; i++)
                states_[i] = temp[i];
        }
        states_[state_ID] = state;
        return state_ID;
    }

    void Check_Components()
    {
        states_ = GetComponents<State>();
        foreach (State state in states_)
        {
            state.Initialize();
        }

        //Init all the states. Fix this issue of doing 
        //states_[i] = idle_;
        //idle_.Initialize(i);

        renderer_ = GetAddComponent<SpriteRenderer>();
        animator_ = GetAddComponent<Animator>();
    }
    T GetAddComponent<T>()
    {
        T component;
        if (GetComponent<T>() == null)
        {
            gameObject.AddComponent(typeof(T));
            Debug.LogError("ADDED " + GetComponent<T>().GetType() + " COMPONENT\nPlease Add Component to the Inspector");
        }
        component = GetComponent<T>();
        return component;
    }

    void Init_Inputs()
    {
        input_Manager_.Add(Button_Names.MOVE_LEFT, Button_State.RELEASED, KeyCode.A);
        input_Manager_.Add(Button_Names.MOVE_RIGHT, Button_State.RELEASED, KeyCode.D);
        input_Manager_.Add(Button_Names.JUMP, Button_State.RELEASED, KeyCode.Space);
    }

    private void Awake()
    {
        Check_Components();
        Init_Inputs();
    }

    private void Update()
    {
        Check_Button_State();
        Handle_Input();
    }

    void Check_Button_State()
    {
        int count_Pressed = 0;
        foreach (KeyValuePair<Button_Names, Input_Manager.Button_Data> button in input_Manager_.button_Dict_)
        {
            if (Input.GetKey(button.Value.key_Code_))
            {
                button.Value.state_ = Button_State.PRESSED;
                count_Pressed++;
            }
            else
                button.Value.state_ = Button_State.RELEASED;
        }
    }

    void Prepare_Inputs()
    {
        if (input_Manager_.button_Dict_[Button_Names.MOVE_LEFT].state_ == Button_State.PRESSED &&
            input_Manager_.button_Dict_[Button_Names.MOVE_RIGHT].state_ == Button_State.PRESSED)
        {
            input_Manager_.button_Dict_[Button_Names.MOVE_LEFT].state_ = Button_State.RELEASED;
            input_Manager_.button_Dict_[Button_Names.MOVE_RIGHT].state_ = Button_State.RELEASED;
        }
    }

    void Handle_Input()
    {
        Prepare_Inputs();

        foreach (KeyValuePair<Button_Names, Input_Manager.Button_Data> button in input_Manager_.button_Dict_)
        {
            switch (current_State_)
            {
                case States.IDLE:
                    states_[(int)States.IDLE].Handle_State(button);
                    break;

                case States.MOVEMENT_LEFT:
                    states_[(int)States.MOVEMENT_LEFT].Handle_State(button);
                    break;
                case States.MOVEMENT_RIGHT:
                    states_[(int)States.MOVEMENT_RIGHT].Handle_State(button);
                    break;

                case States.JUMP:
                    states_[(int)States.JUMP].Handle_State(button);
                    break;
                case States.JUMP_LEFT:
                    states_[(int)States.JUMP_LEFT].Handle_State(button);
                    break;
                case States.JUMP_RIGHT:
                    states_[(int)States.JUMP_RIGHT].Handle_State(button);
                    break;

                case States.FALL:
                    states_[(int)States.FALL].Handle_State(button);
                    break;
                case States.FALL_LEFT:
                    states_[(int)States.FALL_LEFT].Handle_State(button);
                    break;
                case States.FALL_RIGHT:
                    states_[(int)States.FALL_RIGHT].Handle_State(button);
                    break;
            }
        }

        if (Update_State())
            Handle_Input();
    }

    bool Update_State()
    {
        if (next_State_ != current_State_)
        {
            current_State_ = next_State_;

            switch (current_State_)
            {
                case States.IDLE:
                    animator_.Play("Idle");
                    break;
                case States.MOVEMENT_LEFT:
                case States.MOVEMENT_RIGHT:
                    animator_.Play("Run");
                    break;
                case States.JUMP:
                case States.JUMP_LEFT:
                case States.JUMP_RIGHT:
                    animator_.Play("Jump");
                    break;
                case States.FALL:
                case States.FALL_LEFT:
                case States.FALL_RIGHT:
                    animator_.Play("Fall");
                    break;
            }



            //int temp_ID = states_[(int)current_State_].clip_ID_;
            //if (temp_ID == -1)
            //    Debug.LogError("STATE NOT FOUND IN 'Get_State_Clip_ID' Method");

            //animator_.SetInteger("Movement_State", temp_ID);
            return true;
        }
        return false;
    }


    public void Change_State(States new_State)
    {
        next_State_ = new_State;
    }

    public void Change_State(States new_State, bool flip)
    {
        next_State_ = new_State;
        renderer_.flipX = flip;
    }
}
