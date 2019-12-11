using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Movement;

using Key = Input.Key;

public class Player_Controller : MonoBehaviour
{
    Movement_Manager movement_;
    Input input_ = new Input();

    public enum Player_State
    {
        ROOT,
        MOVEMENT,
    }
    public Player_State current_State_;

    private void Awake()
    {
        movement_ = new Movement_Manager(gameObject);

        input_.Init_Keys();

        movement_.Activate_Axis(input_, 10.0f, 15.0f, new Vector3(1.0f, 0.0f, 0.0f), Key.A, Key.D);
        movement_.Activate_Axis(input_, 10.0f, 15.0f, new Vector3(0.0f, 1.0f, 0.0f), Key.S, Key.W);

    }

    int add(int a, int b)
    {
        return a + b;
    }

    private void Update()
    {
        input_.Update_Keys();

        Prepare_Inputs();
        Handle_Inputs();
        Act_Inputs();
        Clear_Inputs();
    }
    
    void Prepare_Inputs()
    {
        while (input_.input_Queue_.Count > 0)
        {
            Key key = input_.input_Queue_.Dequeue();
            Here:
            switch (current_State_)
            {
                case Player_State.ROOT: // Root State
                    current_State_ = Root.Input_Handle(gameObject, Player_State.ROOT, Player_State.MOVEMENT, input_, key);
                    if(current_State_ != Player_State.ROOT)
                        goto Here;
                    break;

                case Player_State.MOVEMENT: // Movement State
                    movement_.Input_Handler(key);
                    if (current_State_ != Player_State.MOVEMENT)
                        goto Here;
                    break;
            }
        }
    }

    void Handle_Inputs()
    {
        current_State_ = movement_.Input_Handler(Player_State.MOVEMENT, Player_State.ROOT);
    }

    void Act_Inputs()
    {
        movement_.Act_Movement();
    }

    void Clear_Inputs()
    {
        movement_.Clear_Movement_Manager();
    }
}