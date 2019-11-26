using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SingletonObjectStates : ScriptableObject
{
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

    public float range_Normal_, range_Triple_, range_Split_;
    public void Set_Range_(float range_Normal, float range_Triple, float range_Split)
    {
        range_Normal_ = range_Normal;
        range_Triple_ = range_Triple;
        range_Split_ = range_Split;
    }
}
