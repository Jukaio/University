using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoulAI : MonoBehaviour
{
    SingletonObjectStates.Soul_State state_;

    public Vector3 acceleration_;
    public Vector3 velocity_;
    public float max_Speed_; 

    Quaternion rotation_;
    Matrix4x4 rotation_Matrix_;

    void Start()
    {
        rotation_ = Quaternion.Euler(20, 0, 0);
        rotation_Matrix_ = Matrix4x4.Rotate(rotation_);
    }

    void Update()
    {
        switch (state_)
        {
            case SingletonObjectStates.Soul_State.INSTANCE:
                state_ = SingletonObjectStates.Soul_State.FLY_FORWARD;
                break;

            case SingletonObjectStates.Soul_State.FLY_UP:
                transform.position -= rotation_Matrix_.MultiplyPoint3x4(velocity_);


                break;

            case SingletonObjectStates.Soul_State.FLY_FORWARD:
                transform.position -= velocity_;
                velocity_ += acceleration_;
                break;
        }
    }
}
