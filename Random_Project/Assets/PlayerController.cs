using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    public SingletonObjectStates.Player_State state_;
    public SingletonObjectStates.Weapon_Type weapon_Type_;



    ////////////////////////////////////////////
    ////////////////////////////////////////////
    ///////// Start and Initialization /////////
    ////////////////////////////////////////////
    ////////////////////////////////////////////

    void Start()
    {
        Init_Bullet_Clip();
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
        bullet_Template_.GetComponent<BulletController>().Set_Data(range_Normal_, range_Triple_, range_Split_, split_angle_, bullet_Speed_.z);

        for (int i = 0; i < bullets_.Count; i++)
        {
            bullets_[i] = Instantiate<GameObject>(bullet_Template_);
        }
    }

    // *END OF START AND INITIALIZATION!

    /////////////////////////////////////////////
    /////////////////////////////////////////////
    ///////// Update and Input Handling /////////
    /////////////////////////////////////////////
    /////////////////////////////////////////////

    void Update()
    {
        Update_States();

        Dodge_Mechanic();
        Choose_Weapon();
        Shooting_Mechanic();
        Update_Cooldowns();
        if (velocity_.x > +max_Speed_)
        {
            velocity_.x = max_Speed_;
        }
    }


    //////////////////////////////
    //// Player State Machine ////
    //////////////////////////////
    void Update_States()
    {
        switch (state_)
        {
            case SingletonObjectStates.Player_State.IDLE:
                Idle_State();
                break;

            case SingletonObjectStates.Player_State.ACCELERATE_LEFT:
                Accelerate_Left_State();
                break;

            case SingletonObjectStates.Player_State.ACCELERATE_RIGHT:
                Accelerate_Right_State();
                break;

            case SingletonObjectStates.Player_State.DEACCELERATE_LEFT:
                Deaccel_Left_State();
                break;

            case SingletonObjectStates.Player_State.DEACCELERATE_RIGHT:
                Deaccel_Right_State();
                break;

            case SingletonObjectStates.Player_State.DODGE_LEFT:
                Dodge_Left_State();
                break;

            case SingletonObjectStates.Player_State.DODGE_RIGHT:
                Dodge_Right_State();
                break;

            default:
                break;
        }
    }


    /////////////////////
    //// Root State  ////
    /////////////////////

    //Idle
    void Idle_State()
    {
        if (Input.GetKey(KeyCode.A) &&
                    Input.GetKey(KeyCode.D))
        {

        }
        else if (Input.GetKey(KeyCode.A))
        {
            state_ = SingletonObjectStates.Player_State.ACCELERATE_LEFT;
        }
        else if (Input.GetKey(KeyCode.D))
        {
            state_ = SingletonObjectStates.Player_State.ACCELERATE_RIGHT;
        }
    }


    //////////////////////////
    //// Movement States  ////
    //////////////////////////

    //Modifiable Data
    public Vector3 acceleration_;
    public Vector3 deacceleration_;
    public float max_Speed_;

    //Data
    public Vector3 velocity_;

    //Acceleration
    void Accelerate_Left_State()
    {
        velocity_ += acceleration_;
        transform.position -= velocity_;
        if (!Input.GetKey(KeyCode.A))
        {
            state_ = SingletonObjectStates.Player_State.DEACCELERATE_LEFT;
        }
    }
    void Accelerate_Right_State()
    {
        velocity_ += acceleration_;
        transform.position += velocity_;
        if (!Input.GetKey(KeyCode.D))
        {
            state_ = SingletonObjectStates.Player_State.DEACCELERATE_RIGHT;
        }
    }

    //Deacceleration
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


    //////////////////////
    //// Dodge State  ////
    //////////////////////

    //Modifiable Data
    public float dodge_Speed_;
    public float dodge_Distance_;
    public float dodge_Cooldown_Max_;

    //Data
    public bool dodge_Done_;
    public float dodge_Cooldown_;
    Vector3 temp_Position_;

    //Check Dodge Input and Conditions
    void Dodge_Mechanic()
    {
        if (dodge_Cooldown_ <= 0)
        {
            if (Input.GetKey(KeyCode.Q))
            {
                state_ = SingletonObjectStates.Player_State.DODGE_LEFT;
            }
            else if (Input.GetKey(KeyCode.E))
            {
                state_ = SingletonObjectStates.Player_State.DODGE_RIGHT;
            }
        }
    }

    //General Dodge
    void Dodge_Left_State()
    {
        if (dodge_Done_)
        {
            temp_Position_ = transform.position; //Init dodge
            dodge_Done_ = false;
            return;
        }

        if (transform.position.x <= temp_Position_.x - dodge_Distance_)
        {
            dodge_Done_ = true;
            state_ = SingletonObjectStates.Player_State.IDLE;
            dodge_Cooldown_ = dodge_Cooldown_Max_;

        }

        transform.position += new Vector3(-dodge_Speed_, 0, 0);
    }
    void Dodge_Right_State()
    {
        if (dodge_Done_)
        {
            temp_Position_ = transform.position; //Init dodge
            dodge_Done_ = false;
            return;
        }

        if (transform.position.x >= temp_Position_.x + dodge_Distance_)
        {
            dodge_Done_ = true;
            state_ = SingletonObjectStates.Player_State.IDLE;
            dodge_Cooldown_ = dodge_Cooldown_Max_;

        }

        transform.position += new Vector3(dodge_Speed_, 0, 0);
    }

    // *END OF PLAYER STATE MACHINE
  

    //////////////////////////////
    //// Weapon State Machine ////
    //////////////////////////////

    //Selection
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

    //Modifiable Data
    public float normal_Shooting_Cooldown_Max_;
    public float triple_Shooting_Cooldown_Max_;
    public float split_Triple_Shooting_Cooldown_Max_;

    //Data
    public float shooting_Cooldown_;

    //Check Weapon Input and Conditions
    void Shooting_Mechanic()
    {
        switch (weapon_Type_)
        {
            case SingletonObjectStates.Weapon_Type.NORMAL:
                Shooting_Normal();
                break;

            case SingletonObjectStates.Weapon_Type.TRIPLE:
                if (Input.GetKey(KeyCode.Space) &&
                    shooting_Cooldown_ == 0)
                {
                    Shooting_Triple();
                }
                break;

            case SingletonObjectStates.Weapon_Type.TRIPLE_SPLIT:
                if (Input.GetKey(KeyCode.Space) &&
                    shooting_Cooldown_ == 0)
                {
                    Shooting_Split_Triple();
                }
                break;

        }
    }

    //Normal Shooting Mode
    //    O
    //    O
    //  |===| <- This is the Player
    void Shooting_Normal()
    {
        if (Input.GetKey(KeyCode.Space) &&
                    shooting_Cooldown_ == 0)
        {

            Shoot_Bullet(0, SingletonObjectStates.Bullet_Type.NORMAL);
            shooting_Cooldown_ = normal_Shooting_Cooldown_Max_;
        }
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
                Shoot_Bullet(i * triple_Offset_, SingletonObjectStates.Bullet_Type.TRIPLE);
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
                Shoot_Bullet(i * triple_Offset_, SingletonObjectStates.Bullet_Type.TRIPLE_SPLIT_MIDDLE + i);
            }
        }
        shooting_Cooldown_ = split_Triple_Shooting_Cooldown_Max_;
    }

    //Dynamic Bullet Activation (Independent from Bullet Behaviour)
    void Shoot_Bullet(float p_x_Modifier, SingletonObjectStates.Bullet_Type p_bullet_Type)
    {
        for (int i = 0; ; i++)
        {
            bullet_Index_++;
            if (bullet_Index_ >= bullets_.Count)
                bullet_Index_ = 0;

            if (bullets_[bullet_Index_].activeSelf == false)
            {
                bullets_[bullet_Index_].transform.position = new Vector3(transform.position.x + p_x_Modifier,
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

        if (dodge_Cooldown_ != 0)
        {
            dodge_Cooldown_ -= Time.deltaTime;
            if (dodge_Cooldown_ < 0)
                dodge_Cooldown_ = 0;
        }

    }

    // *END OF UPDATE COOLDOWNS


    // *END OF UPDATE AND INPUT HANDLING!
}