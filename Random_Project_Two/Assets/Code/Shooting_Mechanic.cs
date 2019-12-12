using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using Key = Custom_Input.Key;

public class Shooting_Mechanic 
{
    enum Shooting_State
    {
        CAN_SHOOT,
        IS_SHOOTING,
        COOLDOWN,
    }
    Shooting_State current_Shoot_State_;

    enum Weapon_Type
    {
        NORMAL,
        TRIPLE,
        TRIPLE_SPLIT
    }

    Key first_, second_, third_, shoot_;
    bool shoot_Pressed_;

    Custom_Input input_;
    GameObject game_Object_;

    public Shooting_Mechanic(GameObject game_Object)
    {
        game_Object_ = game_Object;
    }

    public void Activate_Weapons(Key shoot, Key first = 0, Key second = 0, Key third = 0)
    {
        first_ = first;
        second_ = second;
        third_ = third;
        shoot_ = shoot;
    }

    ///////////////////////////////////////
    //// Bullet Pool and Configuration ////
    ///////////////////////////////////////

    //Modifiable Data
    [SerializeField] private GameObject bullet_Template_;
    [SerializeField] private float range_Normal_, range_Triple_, range_Split_;
    [SerializeField] private float triple_Offset_, split_angle_;
    [SerializeField] private Vector3 bullet_Speed_;

    //Data
    public List<GameObject> bullets_ = new List<GameObject>();
    private short bullet_Index_ = 0;

    //Config and Pooling
    void Init_Bullet_Clip()
    {
        bullet_Template_.SetActive(false);

        for (int i = 0; i < bullets_.Count; i++)
        {
            bullets_[i] = Object.Instantiate<GameObject>(bullet_Template_);
        }
    }

    ///////////////////////
    //// Weapon System ////
    ///////////////////////

    //Selection
    private Weapon_Type weapon_Type_;
    public void Choose_Weapon_State(Key key)
    {
        if (key == Key.NONE)
            return;

        if (key == first_)
        {
            weapon_Type_ = Weapon_Type.NORMAL;
            return;
        }
        else if (key == second_)
        {
            weapon_Type_ = Weapon_Type.TRIPLE;
            return;
        }
        else if (key == third_)
        {
            weapon_Type_ = Weapon_Type.TRIPLE_SPLIT;
            return;
        }
    }

    //Modifiable Data
    public float normal_Shooting_Cooldown_Max_;
    public float triple_Shooting_Cooldown_Max_;
    public float split_Triple_Shooting_Cooldown_Max_;

    //Data
    private float shooting_Cooldown_;



    //Check Weapon Input and Conditions
    public void Act(Key key)
    {
        switch (current_Shoot_State_)
        {
            case Shooting_State.CAN_SHOOT:
                Can_Shoot();
                break;

            case Shooting_State.IS_SHOOTING:
                Shooting();
                break;

            case Shooting_State.COOLDOWN:
                Cooldown();
                break;
        }




        if (key == shoot_ && shooting_Cooldown_ == 0)
        {
            switch (weapon_Type_)
            {
                case Weapon_Type.NORMAL:
                    Shooting_Normal();
                    break;

                case Weapon_Type.TRIPLE:
                    Shooting_Triple();
                    break;

                case Weapon_Type.TRIPLE_SPLIT:
                    Shooting_Split_Triple();
                    break;

            }
        }
    }

    void Can_Shoot()
    {
        //Do it like in Movement_Manager
    }

    void Shooting()
    {

    }

    void Cooldown()
    {

    }


    public void Clear()
    {
        shoot_Pressed_ = false;
    }



    //Normal Shooting Mode
    //    O
    //    O
    //  |===| <- This is the Player
    void Shooting_Normal()
    {

        Vector3 offset = new Vector3(0, 0, 0);
        Vector3 angles = new Vector3(0, 0);

        Shoot_Bullet(offset, angles, range_Normal_);
        shooting_Cooldown_ = normal_Shooting_Cooldown_Max_;

    }

    //Triple Shooting Mode
    //  O O O
    //  O O O
    //  |===| <- This is the Player
    void Shooting_Triple()
    {
        if (Inactive_Bullet_Count() >= 3)
        {
            for (int i = -1; i <= 1; i++)
            {
                Vector3 offset = new Vector3(i * triple_Offset_, 0, 0);
                Vector3 angles = new Vector3(0, 0, 0);
                Shoot_Bullet(offset, angles, range_Triple_);
            }
        }
        shooting_Cooldown_ = triple_Shooting_Cooldown_Max_;
    }

    //Split Triple Shooting Mode
    // O   O   O
    //   O O O
    //   |===| <- This is the Player
    void Shooting_Split_Triple()
    {
        if (Inactive_Bullet_Count() >= 3)
        {
            for (int i = -1; i <= 1; i++)
            {
                Vector3 offset = new Vector3(0, 0, 0);
                Vector3 angles = new Vector3(0, split_angle_ * i, 0);
                Shoot_Bullet(offset, angles, range_Split_);
            }
        }
        shooting_Cooldown_ = split_Triple_Shooting_Cooldown_Max_;
    }

    //Dynamic Bullet Activation (Independent from Bullet Behaviour)
    void Shoot_Bullet(Vector3 origin_modifier, Vector3 angles, float range)
    {
        for (int i = 0; ; i++)
        {
            bullet_Index_++;
            if (bullet_Index_ >= bullets_.Count)
                bullet_Index_ = 0;

            if (bullets_[bullet_Index_].activeSelf == false)
            {
                Vector3 origin = new Vector3(game_Object_.transform.position.x + origin_modifier.x,
                                             game_Object_.transform.position.y + origin_modifier.y,
                                             game_Object_.transform.position.z + origin_modifier.z);

                bullets_[bullet_Index_].GetComponent<Bullet_Controller>().Activate_Bullet(origin, bullet_Speed_, angles, range);
                break;
            }
            if (i >= bullets_.Count - 1)
            {
                break;
            }
        }
    }

    int Inactive_Bullet_Count()
    {
        int count = 0;
        for (int i = 0; i < bullets_.Count; i++)
        {
            if (bullets_[i].activeSelf == false)
                count++;
        }
        return count;
    }

    // *END OF WEAPON STATE MACHINE


    //////////////////////////
    //// Update Cooldowns ////
    //////////////////////////

    public void Update_Cooldowns()
    {
        if (shooting_Cooldown_ != 0)
        {
            if(shooting_Cooldown_ > 0)
                shooting_Cooldown_ -= Time.deltaTime;
            else if (shooting_Cooldown_ < 0)
                shooting_Cooldown_ = 0;
        }

    }

    // *END OF UPDATE COOLDOWNS


    // *END OF UPDATE AND INPUT HANDLING!
}

