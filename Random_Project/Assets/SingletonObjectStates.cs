using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SingletonObjectStates : ScriptableObject
{
    public enum Player_State
    {
        IDLE,
        MOVE_LEFT,
        MOVE_RIGHT,
        DEACCELERATE_LEFT,
        DEACCELERATE_RIGHT,
    }

    public enum Weapon_Type
    {
        NORMAL,
        TRIPLE
    }

    public enum Bullet_Type
    {
        INACTIVE,
        NORMAL,
        TRIPLE
    }
}
