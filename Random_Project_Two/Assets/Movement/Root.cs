using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using Key = Input.Key;
using Player_State = Player_Controller.Player_State;

class Root
{
    static public Player_State Input_Handle(GameObject game_Object, Player_State from, Player_State to, Input input, Key key)
    {
        switch (key)
        {
            case Key.NONE:
                return from;

            case Key.A:
            case Key.D:
                return to;

            case Key.S:
            case Key.W:
                return to;
        }
        return from;
    }
}
    
