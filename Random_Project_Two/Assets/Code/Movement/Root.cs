using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using Key = Custom_Input.Key;
using Player_State = Player_Controller.Player_State;

class Root
{


    public Player_State Input_Handler(GameObject game_Object, Player_State from, Player_State to, Key key)
    {
        switch (key)
        {
            case Key.NONE:
                return from;

            case Key.A:
            case Key.D:
            case Key.S:
            case Key.W:
                return to;
        }
        return from;
    }
}
    
