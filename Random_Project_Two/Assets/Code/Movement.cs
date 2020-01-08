using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using Key = Custom_Input.Key;

public class Movement : MonoBehaviour
{
    public delegate void Handle_Inputs(Key key);

    public void Handle_Input(Key key, Handle_Inputs Handler)
    {
        Handler(key);
    }
}
