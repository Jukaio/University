using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerStates : ScriptableObject
{
    public enum Player_State
    {
        DODGE_LEFT = -4,
        ROTATE_LEFT = -3,
        DECELERATE_LEFT = -2,
        ACCELERATE_LEFT = -1,
        IDLE = 0,
        ACCELERATE_RIGHT,
        DECELERATE_RIGHT,
        ROTATE_RIGHT,
        DODGE_RIGHT,
    }
}
