using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Character_Movement : MonoBehaviour
{
    public enum Character_Movement_State
    {
        LEFT = (int) -1,
        IDLE,
        RIGHT,

    }
    public Character_Movement_State current_Movement_State_;

    Rigidbody2D rigid_Body_2D_;
    Animator animator_;
    SpriteRenderer renderer_;

    public float acceleration_;
    public float max_Velocity_;
    Vector2 direction_ = Vector2.zero;
   


    private void Awake()
    {
        rigid_Body_2D_ = (Rigidbody2D)GetComponent(typeof(Rigidbody2D));
        animator_ = (Animator)GetComponent(typeof(Animator));
        renderer_ = (SpriteRenderer)GetComponent(typeof(SpriteRenderer));
    }


    //public bool Dequeue_Inputs_Move(Button_Names queued_Input)
    //{
    //    switch (current_Movement_State_)
    //    {
    //        case Character_Movement_State.IDLE:

    //            switch (queued_Input)
    //            {
    //                case Button_Names.NONE:
    //                    Change_State(Character_Movement_State.IDLE);
    //                    break;

    //                case Button_Names.MOVE_LEFT:
    //                    goto Move_Left;

    //                case Button_Names.MOVE_RIGHT:
    //                    goto Move_Right;
    //            }
    //            return true;

    //        case Character_Movement_State.LEFT:
    //        Move_Left:
    //            switch (queued_Input)
    //            {
    //                case Button_Names.NONE:
    //                    rigid_Body_2D_.velocity = Vector2.zero;
    //                    break;

    //                case Button_Names.MOVE_LEFT:
    //                    Prepare(Vector2.left);
    //                    break;

    //                case Button_Names.MOVE_RIGHT:
    //                    rigid_Body_2D_.velocity = Vector2.zero;
    //                    goto Move_Right;
    //            }
    //            return true;

    //        case Character_Movement_State.RIGHT:
    //        Move_Right:
    //            switch (queued_Input)
    //            {
    //                case Button_Names.NONE:
    //                    rigid_Body_2D_.velocity = Vector2.zero;
    //                    break;

    //                case Button_Names.MOVE_LEFT:
    //                    rigid_Body_2D_.velocity = Vector2.zero;
    //                    goto Move_Left;

    //                case Button_Names.MOVE_RIGHT:
    //                    Prepare(Vector2.right);
    //                    break;
    //            }
    //            return true;
    //    }
    //    return false;
    //}

    public void Change_State(Character_Movement_State new_State)
    {
        current_Movement_State_ = new_State;
        Enter_State(new_State);
    }

    internal void Enter_State(Character_Movement_State new_State)
    {
        current_Movement_State_ = new_State;
        switch (new_State)
        {
            case Character_Movement_State.IDLE:
                animator_.SetInteger("Movement_State", 0);
                break;

            case Character_Movement_State.LEFT:
                animator_.SetInteger("Movement_State", 1);
                renderer_.flipX = true;
                break;

            case Character_Movement_State.RIGHT:
                animator_.SetInteger("Movement_State", 1);
                renderer_.flipX = false;
                break;
        }
    }

    private void Prepare(Vector2 direction)
    {
        direction_ += direction;
    }

    public void Execute()
    {
        Change_State((Character_Movement_State)((int)direction_.x));
        if (rigid_Body_2D_.velocity.x * direction_.x < max_Velocity_)
            rigid_Body_2D_.velocity += acceleration_ * direction_;

    }

    public void Clear()
    {
        direction_ = Vector2.zero;
    }
}

