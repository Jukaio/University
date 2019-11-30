using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ControlLayout : MonoBehaviour
{
    public KeyCode move_Left_;
    public KeyCode move_Right_;
    public KeyCode dodge_Left_;
    public KeyCode dodge_Right_;

    public KeyCode move_Left_3D_;
    public KeyCode move_Right_3D_;
    public KeyCode move_Down_3D_;
    public KeyCode move_Up_3D_;

    public KeyCode shoot_;

    public KeyCode weapon_Slot_1_;
    public KeyCode weapon_Slot_2_;
    public KeyCode weapon_Slot_3_;

    bool double_Move_Left;
    bool double_Move_Right;

    float tap_Cooldown_ = 0.5f;
    int button_Count_ = 0;

    void Update()
    {
        if(Input.GetKeyDown(move_Left_))
        {
            if (tap_Cooldown_ >= 0 && button_Count_ == 1)
            {
                double_Move_Left = true;
            }
            else
            {
                tap_Cooldown_ = 0.5f;
                button_Count_ += 1;
            }
        }

        if(tap_Cooldown_ > 0)
        {
            tap_Cooldown_ -= Time.deltaTime;
        }
        else
        {
            button_Count_ = 0;
        }
    }
}
