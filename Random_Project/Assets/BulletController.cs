using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletController : MonoBehaviour
{
    public Vector3 bullet_Speed_;
    float range_;
    public Vector3 distance_Travelled_ = Vector3.zero;
    public Vector3 shoot_Angles_;

    void Update()
    {
        Update_Bullet();
        Reset_Bullet();
    }

    public void Activate_Bullet(Vector3 origin, Vector3 speed, Vector3 angles, float range)
    {
        transform.position = origin;
        range_ = range;
        bullet_Speed_ = speed;
        shoot_Angles_ = angles;
        gameObject.SetActive(true);
    }

    void Update_Bullet()
    {
        Bullet_Transformation(bullet_Speed_, shoot_Angles_);
    }

    void Bullet_Transformation(Vector3 direction, Vector3 angles)
    {
        Quaternion rotation = Quaternion.Euler(angles);
        Matrix4x4 rotation_Matrix = Matrix4x4.Rotate(rotation);

        transform.Translate(rotation_Matrix.MultiplyPoint3x4(direction));
        distance_Travelled_ += rotation_Matrix.MultiplyPoint3x4(direction);
    }

    void Reset_Bullet()
    {
        if (distance_Travelled_.magnitude >= range_)
        {
            distance_Travelled_ = Vector3.zero;
            gameObject.SetActive(false);
        }
    }
}
