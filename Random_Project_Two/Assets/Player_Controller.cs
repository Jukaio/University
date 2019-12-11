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

        movement_.Activate_Axis(input_, 2.0f, 2.0f, new Vector3(1.0f, 0.0f, 0.0f), Key.A, Key.D);
    }

    private void Update()
    {
        input_.Update_Keys();

        State_Update();
        State_Act();
    }

    void State_Update()
    {
        while (input_.input_Queue_.Count > 0)
        {
            Key key = input_.input_Queue_.Dequeue();

            switch (current_State_)
            {
                case Player_State.ROOT: // Root State
                    current_State_ = Root.Input_Handle(gameObject, Player_State.ROOT, Player_State.MOVEMENT, input_, key);
                    break;

                case Player_State.MOVEMENT: // Movement State
                    current_State_ = movement_.Input_Handler(Player_State.MOVEMENT, Player_State.ROOT);
                    break;
            }
        }
    }

    void State_Act()
    {
         //Make this shit smart
    }
}