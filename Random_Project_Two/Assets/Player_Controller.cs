using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using Key = Input.Key;

public class Player_Controller : MonoBehaviour
{
    Player_Controller controller_;
    Movement movement_ = new Movement();

    public enum Player_State
    {
        ROOT,
        MOVEMENT,
    }
    public Player_State current_State;

    Input input_ = new Input();

    private void Start()
    {
        controller_ = this;
        input_.Init_Keys();
    }

    private void Update()
    {
        input_.Update_Keys();

        Check_State();
    }

    void Check_State()
    {
        while (input_.input_Queue_.Count > 0)
        {
            Key input = input_.input_Queue_.Dequeue();

            switch (current_State)
            {
                case Player_State.ROOT: // Root State

                    break;

                case Player_State.MOVEMENT: // Movement State
                    movement_.Input_Handle(input_, input);
                    break;
            }
        }
    }
}