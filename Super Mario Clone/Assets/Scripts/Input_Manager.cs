using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public enum Button_Names
{
    MOVE_LEFT,
    MOVE_RIGHT,
    JUMP,
}

public enum Button_State
{
    PRESSED,
    RELEASED
}

public class Input_Manager
{
    public class Button_Data
    {
        public Button_State state_;
        public KeyCode key_Code_;
    }

    public Dictionary<Button_Names, Button_Data> button_Dict_ = new Dictionary<Button_Names, Button_Data>();



    public void Add(Button_Names n, Button_State s, KeyCode k)
    {
        Button_Data button_Data = new Button_Data();
        button_Data.key_Code_ = k;
        button_Data.state_ = s;


        if (button_Dict_.ContainsKey(n))
            button_Dict_.Remove(n);
        button_Dict_.Add(n, button_Data);
    }

    public void Change(Button_Names a, KeyCode k)
    {
        //to do
    }

}

