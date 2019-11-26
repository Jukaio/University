using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Command : ScriptableObject
{
    static public int check_Axis_(KeyCode minus, KeyCode plus)
    {
        if (Input.GetKey(minus) && Input.GetKeyDown(plus))
            return 0;
        if (Input.GetKey(minus) && !Input.GetKeyDown(plus))
            return -1;
        if (Input.GetKey(plus) && !Input.GetKeyDown(minus))
            return 1;
        return 0;
    }

    static public bool check_Pressed_(KeyCode button)
    {
        return Input.GetKeyDown(button);
    }

    static public bool check_Released_(KeyCode button)
    {
        return Input.GetKeyUp(button);
    }


}
