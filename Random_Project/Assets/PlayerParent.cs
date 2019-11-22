using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerParent : MonoBehaviour
{
    public GameObject player_Parent;
    public SingletonObjectStates state_Param_;

    private void Awake()
    {
        state_Param_ = (SingletonObjectStates)ScriptableObject.CreateInstance(typeof(SingletonObjectStates));
    }

    SingletonObjectStates Get_State_Param()
    {
        return state_Param_;
    }
}
