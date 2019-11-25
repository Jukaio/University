using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShootingMechanic : MonoBehaviour
{
    void Start()
    {
        Init_Bullet_Clip();
    }
    
    void Update()
    {
        Update_Cooldowns();
    }

    ///////////////////////////////////////
    //// Bullet Pool and Configuration ////
    ///////////////////////////////////////

    //Modifiable Data
    public GameObject bullet_Template_;
    public float range_Normal_, range_Triple_, range_Split_;
    public float triple_Offset_, split_angle_;
    public Vector3 bullet_Speed_;

    //Data
    public List<GameObject> bullets_ = new List<GameObject>();
    private short bullet_Index_ = 0;

    //Config and Pooling
    void Init_Bullet_Clip()
    {
        bullet_Template_.SetActive(false);

        for (int i = 0; i < bullets_.Count; i++)
        {
            bullets_[i] = Instantiate<GameObject>(bullet_Template_);
        }
    }

    ///////////////////////
    //// Weapon System ////
    ///////////////////////

    //Selection
    public SingletonObjectStates.Weapon_Type weapon_Type_;
    public void Choose_Weapon()
    {
        if (Input.GetKey(KeyCode.Alpha1))
        {
            weapon_Type_ = SingletonObjectStates.Weapon_Type.NORMAL;
        }
        else if (Input.GetKey(KeyCode.Alpha2))
        {
            weapon_Type_ = SingletonObjectStates.Weapon_Type.TRIPLE;
        }
        else if (Input.GetKey(KeyCode.Alpha3))
        {
            weapon_Type_ = SingletonObjectStates.Weapon_Type.TRIPLE_SPLIT;
        }
    }

    //Modifiable Data
    public float normal_Shooting_Cooldown_Max_;
    public float triple_Shooting_Cooldown_Max_;
    public float split_Triple_Shooting_Cooldown_Max_;

    //Data
    public float shooting_Cooldown_;

    //Check Weapon Input and Conditions
    public void Shooting_Mechanic()
    {
        if (Input.GetKey(KeyCode.Space) &&
            shooting_Cooldown_ == 0)
        {
            switch (weapon_Type_)
            {
                case SingletonObjectStates.Weapon_Type.NORMAL:
                    Shooting_Normal();
                    break;

                case SingletonObjectStates.Weapon_Type.TRIPLE:
                    Shooting_Triple();
                    break;

                case SingletonObjectStates.Weapon_Type.TRIPLE_SPLIT:
                    Shooting_Split_Triple();
                    break;

            }
        }
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
                Vector3 origin = new Vector3(transform.position.x + origin_modifier.x,
                                             transform.position.y + origin_modifier.y,
                                             transform.position.z + origin_modifier.z);

                bullets_[bullet_Index_].GetComponent<BulletController>().Activate_Bullet(origin, bullet_Speed_, angles, range);
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

    void Update_Cooldowns()
    {
        if (shooting_Cooldown_ != 0)
        {
            shooting_Cooldown_ -= Time.deltaTime;
            if (shooting_Cooldown_ < 0)
                shooting_Cooldown_ = 0;
        }

    }

    // *END OF UPDATE COOLDOWNS


    // *END OF UPDATE AND INPUT HANDLING!
}
