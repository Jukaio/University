using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Movement;

using Key = Input.Key;

public class Player_Controller : MonoBehaviour
{
    List<Movement_Manager> movement_ = new List<Movement_Manager>();
    Input input_ = new Input();

    public enum Player_State
    {
        ROOT,
        MOVEMENT,
    }
    public Player_State current_State_;

    private void Awake()
    {
        movement_.Add(new Movement_Manager(gameObject, Key.A, Key.D));
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
            Key key = input_.input_Queue_.Dequeue();

            switch (current_State_)
            {
                case Player_State.ROOT: // Root State
                    current_State_ = Root.Input_Handle(gameObject, Player_State.ROOT, Player_State.MOVEMENT, input_, key);
                    break;

                case Player_State.MOVEMENT: // Movement State
                    current_State_ = movement_[0].Input_Handler(Player_State.MOVEMENT, Player_State.ROOT, input_, key);
                    break;
            }
        }
    }
}