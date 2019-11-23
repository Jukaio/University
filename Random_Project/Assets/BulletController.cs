using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletController : MonoBehaviour
{
    SingletonObjectStates state_Param_;
    public SingletonObjectStates.Bullet_Type bullet_Type_;

    public Vector3 bullet_Speed_;
    float range_;
    public float range_Normal_, range_Triple_, range_Split_;
    public Vector3 shoot_Angles_;
    Matrix4x4 rotation_Matrix_Positive_;
    Matrix4x4 rotation_Matrix_Negative_;
    Vector3 vec;

    public void Set_Data(float p_Range_Normal, float p_Range_Triple, float p_Range_Split, float p_Angle_Split, float p_Bullet_Speed)
    {
        range_Normal_ = p_Range_Normal;
        range_Triple_ = p_Range_Triple;
        range_Split_ = p_Range_Split;
        shoot_Angles_.y = p_Angle_Split;
        bullet_Speed_.z = p_Bullet_Speed;
    }

    void Awake()
    {
        Init_Bullet_Param();
    }

    void OnEnable()
    {
        Init_Bullet();
    }

    // Update is called once per frame
    void Update()
    {
        Update_Bullet();
        Reset_Bullet();
    }

    public void Set_Bullet_Type(SingletonObjectStates.Bullet_Type type)
    {
        bullet_Type_ = type;
    }
    void Init_Bullet_Param()
    {
        Quaternion rotation = Quaternion.Euler(shoot_Angles_.x, shoot_Angles_.y, shoot_Angles_.z);
        rotation_Matrix_Positive_ = Matrix4x4.Rotate(rotation);
        rotation = Quaternion.Euler(-shoot_Angles_.x, -shoot_Angles_.y, -shoot_Angles_.z);
        rotation_Matrix_Negative_ = Matrix4x4.Rotate(rotation);
        vec = new Vector3(0, 0, range_Split_);
        vec = rotation_Matrix_Negative_.MultiplyPoint3x4(vec);
    }
    void Init_Bullet()
    {
        switch (bullet_Type_)
        {
            case SingletonObjectStates.Bullet_Type.NORMAL:
                range_ = range_Normal_;
                break;

            case SingletonObjectStates.Bullet_Type.TRIPLE:
                range_ = range_Triple_;
                break;

            case SingletonObjectStates.Bullet_Type.TRIPLE_SPLIT_LEFT:
                range_ = vec.z;
                break;
            case SingletonObjectStates.Bullet_Type.TRIPLE_SPLIT_MIDDLE:
                range_ = range_Split_;
                break;
            case SingletonObjectStates.Bullet_Type.TRIPLE_SPLIT_RIGHT:
                range_ = vec.z;
                break;
        }
    }
    void Update_Bullet()
    {
        switch (bullet_Type_)
        {
            case SingletonObjectStates.Bullet_Type.NORMAL:
                transform.position += bullet_Speed_;
                break;

            case SingletonObjectStates.Bullet_Type.TRIPLE:
                transform.position += bullet_Speed_;
                break;

            case SingletonObjectStates.Bullet_Type.TRIPLE_SPLIT_LEFT:
                transform.position += (rotation_Matrix_Negative_.MultiplyPoint3x4(bullet_Speed_));
                break;

            case SingletonObjectStates.Bullet_Type.TRIPLE_SPLIT_MIDDLE:
                transform.position += bullet_Speed_;
                break;

            case SingletonObjectStates.Bullet_Type.TRIPLE_SPLIT_RIGHT:
                transform.position += (rotation_Matrix_Positive_.MultiplyPoint3x4(bullet_Speed_));
                break;
        }
    }
    void Reset_Bullet()
    {
        if (transform.position.z >= range_)
        {
            gameObject.SetActive(false);
        }
    }
}
