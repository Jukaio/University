using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SingletonObjectStates : ScriptableObject
{
    public enum Player_State
    {
        IDLE = 0,
    }
    public enum Weapon_Type
    {
        NORMAL,
        TRIPLE,
        TRIPLE_SPLIT,
    }

    public enum Soul_State
    {
        INSTANCE,
        FLY_FORWARD,
        FLY_UP,
    }
}
