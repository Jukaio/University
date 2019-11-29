using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class PlayerStates : ScriptableObject
{
    public enum Player_State
    {
        IDLE = 0,
        ACCELERATION,
        MAX_SPEED,
        DECELERATION,
        COUNTERCELERATION,
        DODGE,
        DODGE_DECELERATION,
        DODGE_COUNTERCELERATION,
    }
}
