using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    SingletonObjectStates state_Param_;

    public SingletonObjectStates.Player_State state_;
    public SingletonObjectStates.Weapon_Type weapon_Type_;

    public Vector3 velocity_;
    public Vector3 acceleration_;
    public Vector3 deacceleration_;

    public GameObject bullet_Template_;
    public Vector3 bullet_Speed_;
    public float triple_Distance_;
    public List<GameObject> bullets_ = new List<GameObject>();
    private short bullet_Index_ = 0;
    public float shooting_Cooldown_;
    public float shooting_Cooldown_Max_;


    void Awake()
    {
        for(int i = 0; i < bullets_.Count; i++)
        {
            bullets_[i] = Instantiate<GameObject>(bullet_Template_);
            bullets_[i].transform.parent = transform.parent;
            bullets_[i].SetActive(false);
            bullets_[i].GetComponent<BulletController>().bullet_Speed_ = bullet_Speed_;
        }
    }

    void Update()
    {
        Update_States();

        Choose_Weapon();
        Shooting_Mechanic();
        Update_Cooldowns();
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

                    Shoot_Bullet(0);
                    shooting_Cooldown_ = shooting_Cooldown_Max_;
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
                            Shoot_Bullet(i * triple_Distance_);
                        }
                    }
                    shooting_Cooldown_ = shooting_Cooldown_Max_;
                }
                break;
        }
    }

    void Shoot_Bullet(float x_Modifier)
    {
        for (int i = 0; ; i++)
        {
            bullet_Index_++;
            if (bullet_Index_ >= bullets_.Count)
                bullet_Index_ = 0;

            if (bullets_[bullet_Index_].activeSelf == false)
            {
                
                bullets_[bullet_Index_].transform.Translate(new Vector3(transform.position.x + x_Modifier,
                                                                transform.position.y,
                                                                transform.position.z));
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
        if (shooting_Cooldown_ != 0)
        {
            shooting_Cooldown_ -= Time.deltaTime;
            if (shooting_Cooldown_ < 0)
                shooting_Cooldown_ = 0;
        }
    }
}
