using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using Key = Input.Key;

class Movement : Player_Controller
{
    enum Movement_State
    {
        ACCELERATE,
        HIGH_SPEED,
        DECELERATE,
    }

    float velocity_;

    public void Input_Handle(Input input, Key key)
    {
        switch (key)
        {
            case Key.NONE:
                break;

            case Key.A:
            case Key.D:
                transform.position += new Vector3(input.input_on_axis(Key.A, Key.D), 0, 0);
                

                break;

            case Key.S:
            case Key.W:

                break;
        }
    }

    void Acceleration()
    {

    }

    void High_Speed()
    {

    }

    void Deceleration()
    {

    }

}

