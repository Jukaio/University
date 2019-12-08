using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using Easing;


class Acceleration
{
    static EasingFunction.Function Ease = EasingFunction.GetEasingFunction(EasingFunction.Ease.EaseInSine);

    public static float Raise_Velocity(float target, float t, float speed)
    {
        double temp = Ease(t) * speed;

        return target * (float)temp;
    }
}

