using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    //Change accessibility and change triple-split to multi-split. Make it more dynamic :) 
    //Sort in the variables above the functions
    public SingletonObjectStates.Player_State state_;
    public SingletonObjectStates.Weapon_Type weapon_Type_;

    public Vector3 velocity_;
    public Vector3 acceleration_;
    public Vector3 deacceleration_;

    float range_Normal_, range_Triple_, range_Split_;
    public GameObject bullet_Template_;
    public Vector3 bullet_Speed_;
    public float triple_Distance_;
    public List<GameObject> bullets_ = new List<GameObject>();
    private short bullet_Index_ = 0;

    public float shooting_Cooldown_;

    public float normal_Shooting_Cooldown_;
    public float normal_Shooting_Cooldown_Max_;

    public float triple_Shooting_Cooldown_;
    public float triple_Shooting_Cooldown_Max_;

    public float split_Triple_Shooting_Cooldown_;
    public float split_Triple_Shooting_Cooldown_Max_;

    void Start()
    {
        Init_Bullet_Clip();
    }

    void Update()
    {
        Update_States();

        Choose_Weapon();
        Shooting_Mechanic();
        Update_Cooldowns();
    }

    void Init_Bullet_Clip() //Bullet POol
    {
        bullet_Template_.SetActive(false);
        bullet_Template_.GetComponent<BulletController>().bullet_Speed_ = bullet_Speed_;

        for (int i = 0; i < bullets_.Count; i++)
        {
            bullets_[i] = Instantiate<GameObject>(bullet_Template_);
        }
    }

    void Choose_Weapon()
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

    void Update_States()
    {
        switch (state_)
        {
            case SingletonObjectStates.Player_State.IDLE:
                Idle_State();
                break;

            case SingletonObjectStates.Player_State.MOVE_LEFT:
                Move_Left_State();
                break;

            case SingletonObjectStates.Player_State.MOVE_RIGHT:
                Move_Right_State();
                break;

            case SingletonObjectStates.Player_State.DEACCELERATE_LEFT:
                Deaccel_Left_State();
                break;

            case SingletonObjectStates.Player_State.DEACCELERATE_RIGHT:
                Deaccel_Right_State();
                break;

            default:

                break;
        }
    }

    void Idle_State()
    {
        if (Input.GetKey(KeyCode.A) &&
                    Input.GetKey(KeyCode.D))
        {

        }
        else if (Input.GetKey(KeyCode.A))
        {
            state_ = SingletonObjectStates.Player_State.MOVE_LEFT;
        }
        else if (Input.GetKey(KeyCode.D))
        {
            state_ = SingletonObjectStates.Player_State.MOVE_RIGHT;
        }
    }

    void Move_Left_State()
    {
        velocity_ += acceleration_;
        transform.position -= velocity_;
        if (!Input.GetKey(KeyCode.A))
        {
            state_ = SingletonObjectStates.Player_State.DEACCELERATE_LEFT;
        }
    }

    void Move_Right_State()
    {
        velocity_ += acceleration_;
        transform.position += velocity_;
        if (!Input.GetKey(KeyCode.D))
        {
            state_ = SingletonObjectStates.Player_State.DEACCELERATE_RIGHT;
        }
    }

    void Deaccel_Left_State()
    {
        if (velocity_.x > 0)
        {
            velocity_ -= deacceleration_;
            transform.position -= velocity_;
        }
        else
        {
            velocity_ = Vector3.zero;
            state_ = SingletonObjectStates.Player_State.IDLE;
        }
    }

    void Deaccel_Right_State()
    {
        if (velocity_.x > 0)
        {
            velocity_ -= deacceleration_;
            transform.position += velocity_;
        }
        else
        {
            velocity_ = Vector3.zero;
            state_ = SingletonObjectStates.Player_State.IDLE;
        }
    }

    void Shooting_Mechanic()
    {
        switch (weapon_Type_)
        {
            case SingletonObjectStates.Weapon_Type.NORMAL:
                if (Input.GetKey(KeyCode.Space) &&
                    shooting_Cooldown_ == 0)
                {

                    Shoot_Bullet(0, SingletonObjectStates.Bullet_Type.NORMAL);
                    shooting_Cooldown_ = normal_Shooting_Cooldown_Max_;
                }
                break;

            case SingletonObjectStates.Weapon_Type.TRIPLE:
                if (Input.GetKey(KeyCode.Space) &&
                    shooting_Cooldown_ == 0)
                {
                    if (Inactive_Bullet_Count() >= 3)
                    {
                        for (int i = -1; i <= 1; i++)
                        {
                            Shoot_Bullet(i * triple_Distance_, SingletonObjectStates.Bullet_Type.TRIPLE);
                        }
                    }
                    shooting_Cooldown_ = triple_Shooting_Cooldown_Max_;
                }
                break;

            case SingletonObjectStates.Weapon_Type.TRIPLE_SPLIT:
                if (Input.GetKey(KeyCode.Space) &&
                    shooting_Cooldown_ == 0)
                {
                    if (Inactive_Bullet_Count() >= 3)
                    {
                        for (int i = -1; i <= 1; i++)
                        {
                            Shoot_Bullet(i * triple_Distance_, SingletonObjectStates.Bullet_Type.TRIPLE_SPLIT_MIDDLE + i);
                        }
                    }
                    shooting_Cooldown_ = split_Triple_Shooting_Cooldown_Max_;
                }
                break;

        }
    }

    void Shoot_Bullet(float x_Modifier, SingletonObjectStates.Bullet_Type p_bullet_Type)
    {
        for (int i = 0; ; i++)
        {
            bullet_Index_++;
            if (bullet_Index_ >= bullets_.Count)
                bullet_Index_ = 0;

            if (bullets_[bullet_Index_].activeSelf == false)
            {
                bullets_[bullet_Index_].transform.position = new Vector3(transform.position.x + x_Modifier,
                                                                transform.position.y,
                                                                transform.position.z);
                bullets_[bullet_Index_].GetComponent<BulletController>().Set_Bullet_Type(p_bullet_Type);
                bullets_[bullet_Index_].SetActive(true);
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
        for (int i = 0; i < bullets_.Count ; i++)
        {
            if (bullets_[i].activeSelf == false)
                count++;
        }
        return count;
    }

    void Update_Cooldowns()
    {
        if (normal_Shooting_Cooldown_ != 0)
        {
            normal_Shooting_Cooldown_ -= Time.deltaTime;
            if (normal_Shooting_Cooldown_ < 0)
                normal_Shooting_Cooldown_ = 0;
        }

        if (triple_Shooting_Cooldown_ != 0)
        {
            triple_Shooting_Cooldown_ -= Time.deltaTime;
            if (triple_Shooting_Cooldown_ < 0)
                triple_Shooting_Cooldown_ = 0;
        }

        if (split_Triple_Shooting_Cooldown_ != 0)
        {
            split_Triple_Shooting_Cooldown_ -= Time.deltaTime;
            if (split_Triple_Shooting_Cooldown_ < 0)
                split_Triple_Shooting_Cooldown_ = 0;
        }

        if (shooting_Cooldown_ != 0)
        {
            shooting_Cooldown_ -= Time.deltaTime;
            if (shooting_Cooldown_ < 0)
                shooting_Cooldown_ = 0;
        }

    }
}
