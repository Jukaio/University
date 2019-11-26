using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovementMechanic : MonoBehaviour
{
    public Vector3 velocity_;
    [SerializeField] private Vector3 acceleration_;
    [SerializeField] private float counter_Deceleration_Factor_;
    [SerializeField] private Vector3 deceleration_;
    [SerializeField] private float max_Speed_x_;

    void Awake()
    {
        Init_Default();
    }

    void Update()
    {
        Correction();
    }

    void Init_Default()
    {
        if (counter_Deceleration_Factor_ == 0)
        {
            counter_Deceleration_Factor_ = 1;
        }

    }

    void Correction()
    {
        if (velocity_.x > max_Speed_x_)
            velocity_.x = max_Speed_x_;
    }

    public void Accelerate(int direction)
    {
        velocity_ += acceleration_;
        transform.position += velocity_ * direction;
    }

    public bool Decelerate(int direction)
    {
        if (velocity_.x >= 0)
        {
            velocity_ -= deceleration_;
            transform.position -= velocity_ * direction;
            return false;
        }
        velocity_ = Vector3.zero;
        return true;

    }

    public bool Counter_Accelerate(int direction)
    {
        if (velocity_.x >= 0)
        {
            velocity_ -= deceleration_ * counter_Deceleration_Factor_;
            transform.position -= velocity_ * direction;
            return false;
        }
        velocity_ = Vector3.zero;
        return true;
    }
}