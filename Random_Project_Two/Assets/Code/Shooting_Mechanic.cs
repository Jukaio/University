using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using Key = Custom_Input.Key;

public class Shooting_Mechanic
{
    enum Shooting_State
    {
        CAN_SHOOT,
        SHOOTING,
        COOLDOWN,
    }
    Shooting_State current_Shoot_State_;

    public enum Weapon_Type
    {
        NORMAL,
        TRIPLE,
        TRIPLE_SPLIT
    }
    private Weapon_Type weapon_Type_;

    Key first_ = 0, second_ = 0, third_ = 0, shoot_ = 0;
    bool shoot_Pressed_;

    GameObject game_Object_;
    AudioSource audio_Source_;

    //Modifiable Data
    private GameObject bullet_Template_;
    private float range_Normal_, range_Triple_, range_Split_;
    private float triple_Offset_, split_angle_;
    private Vector3 bullet_Speed_One_, bullet_Speed_Two_, bullet_Speed_Three_ = Vector3.zero;

    public float normal_Shooting_Cooldown_Max_;
    public float triple_Shooting_Cooldown_Max_;
    public float split_Triple_Shooting_Cooldown_Max_;

    //Data
    public List<GameObject> bullets_One_ = new List<GameObject>();
    public List<GameObject> bullets_Two_ = new List<GameObject>();
    public List<GameObject> bullets_Three_ = new List<GameObject>();
    private short bullet_Index_ = 0;

    private float shooting_Cooldown_;

    List<GameObject> get_Clip(Weapon_Type weapon)
    {
        switch (weapon)
        {
            case Weapon_Type.NORMAL:
                return bullets_One_;

            case Weapon_Type.TRIPLE:
                return bullets_Two_;

            case Weapon_Type.TRIPLE_SPLIT:
                return bullets_Three_;
        }
        return new List<GameObject>();
    }



    public Shooting_Mechanic(GameObject game_Object)
    {
        game_Object_ = game_Object;
        audio_Source_ = game_Object_.GetComponent<Player_Controller>().audio_Source_Clip_;
    }

    public void Activate_Shooting(Key shoot)
    {
        shoot_ = shoot;
    }

    public void Activate_Weapon_One(Key key, float range, float speed, float cooldown)
    {
        first_ = key;
        range_Normal_ = range;
        bullet_Speed_One_ = new Vector3(0, 0, speed);
        normal_Shooting_Cooldown_Max_ = cooldown;
    }

    public void Activate_Weapon_Two(Key key, float range, float speed, float offset, float cooldown)
    {
        second_ = key;
        range_Triple_ = range;
        triple_Offset_ = offset;
        bullet_Speed_Two_ = new Vector3(0, 0, speed);
        triple_Shooting_Cooldown_Max_ = cooldown;
    }

    public void Activate_Weapon_Three(Key key, float range, float speed, float angle, float cooldown)
    {
        third_ = key;
        range_Split_ = range;
        split_angle_ = angle;
        bullet_Speed_Three_ = new Vector3(0, 0, speed);
        split_Triple_Shooting_Cooldown_Max_ = cooldown;
    }

    ///////////////////////////////////////
    //// Bullet Pool and Configuration ////
    ///////////////////////////////////////

    //Config and Pooling
    public void Init_Bullet_Clip(int clip_Size, Weapon_Type weapon, GameObject template)
    {
        template.SetActive(false);

        switch (weapon)
        {
            case Weapon_Type.NORMAL:
                for (int i = 0; i < clip_Size; i++)
                {
                    bullets_One_.Add(Object.Instantiate<GameObject>(template));
                }
                break;
            case Weapon_Type.TRIPLE:
                for (int i = 0; i < clip_Size; i++)
                {
                    bullets_Two_.Add(Object.Instantiate<GameObject>(template));
                }
                break;
            case Weapon_Type.TRIPLE_SPLIT:
                for (int i = 0; i < clip_Size; i++)
                {
                    bullets_Three_.Add(Object.Instantiate<GameObject>(template));
                }
                break;
        }
    }

    ///////////////////////
    //// Weapon System ////
    ///////////////////////

    //Selection
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

    public void Gather_Input(Key key) // Sets "Dual" Input
    {
        if (key == shoot_)
            shoot_Pressed_ = true;
    }

    //Check Weapon Input and Conditions
    public void Act()
    {
        switch (current_Shoot_State_)
        {
            case Shooting_State.CAN_SHOOT:
                if (Can_Shoot())
                    goto case Shooting_State.SHOOTING;
                break;

            case Shooting_State.SHOOTING:
                Shooting();
                break;

            case Shooting_State.COOLDOWN:
                Cooldown();
                break;
        }
    }

    bool Can_Shoot()
    {
        if (shoot_Pressed_)
            return true;
        return false;
    }

    void Shooting()
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
        current_Shoot_State_ = Shooting_State.COOLDOWN;
    }

    void Cooldown()
    {
        shooting_Cooldown_ -= Time.deltaTime;
        if (shooting_Cooldown_ < 0)
        {
            current_Shoot_State_ = Shooting_State.CAN_SHOOT;
        }
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
        if (Inactive_Bullet_Count() >= 1)
        {
            Shoot_Bullet(offset, angles, range_Normal_, bullet_Speed_One_);
        }
        else //This way we can have endless shooting!
        {
            GameObject temp = Object.Instantiate<GameObject>(get_Clip(weapon_Type_)[0]);
            temp.SetActive(false);
            get_Clip(weapon_Type_).Add(temp);
            Shooting_Normal();
        }
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
                Shoot_Bullet(offset, angles, range_Triple_, bullet_Speed_Two_);
            }
        }
        else //This way we can have reload stuff
        if (!audio_Source_.isPlaying)
            audio_Source_.Play();
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
                Shoot_Bullet(offset, angles, range_Split_, bullet_Speed_Three_);
            }
        }
        else
        if (!audio_Source_.isPlaying)
            audio_Source_.Play();
        shooting_Cooldown_ = split_Triple_Shooting_Cooldown_Max_;
    }

    //Dynamic Bullet Activation (Independent from Bullet Behaviour)
    void Shoot_Bullet(Vector3 origin_modifier, Vector3 angles, float range, Vector3 bullet_Speed)
    {
        for (int i = 0; ; i++)
        {
            bullet_Index_++;
            if (bullet_Index_ >= get_Clip(weapon_Type_).Count)
                bullet_Index_ = 0;

            if (get_Clip(weapon_Type_)[bullet_Index_].activeSelf == false)
            {
                Vector3 origin = new Vector3(game_Object_.transform.position.x + origin_modifier.x,
                                             game_Object_.transform.position.y + origin_modifier.y,
                                             game_Object_.transform.position.z + origin_modifier.z);

                get_Clip(weapon_Type_)[bullet_Index_].GetComponent<Bullet_Controller>().Activate_Bullet(origin, bullet_Speed, angles, range);
                return;
            }


            if (i >= get_Clip(weapon_Type_).Count - 1)
            {
                break;
            }
        }
    }

    int Inactive_Bullet_Count()
    {
        int count = 0;
        for (int i = 0; i < get_Clip(weapon_Type_).Count; i++)
        {
            if (get_Clip(weapon_Type_)[i].activeSelf == false)
                count++;
        }
        return count;
    }

    // *END OF WEAPON STATE MACHINE



    // *END OF UPDATE AND INPUT HANDLING!
}

