using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet_Controller : MonoBehaviour
{
    public Vector3 bullet_Speed_;
    float range_;
    public Vector3 distance_Travelled_ = Vector3.zero;
    public Vector3 shoot_Angles_;

    AudioSource audio_Source_;

    void Update()
    {
        Update_Bullet();
        Reset_Bullet();
    }

    private void Awake()
    {
        audio_Source_ = GetComponent<AudioSource>();
    }

    public void Activate_Bullet(Vector3 origin, Vector3 speed, Vector3 angles, float range)
    {
        transform.position = origin;
        range_ = range;
        bullet_Speed_ = speed;
        shoot_Angles_ = angles;
        gameObject.SetActive(true);
        audio_Source_.Play();
    }

    void Update_Bullet()
    {
        Bullet_Transformation(bullet_Speed_ * Time.deltaTime, shoot_Angles_);
    }

    void Bullet_Transformation(Vector3 direction, Vector3 angles)
    {
        Quaternion rotation = Quaternion.Euler(angles);
        Matrix4x4 rotation_Matrix = Matrix4x4.Rotate(rotation);
        Vector3 temp = rotation_Matrix.MultiplyPoint3x4(direction);
        transform.position += temp;
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

    private void OnTriggerEnter(Collider other)
    {
        if (other.name.Contains("Capsule"))
        {
            distance_Travelled_ = Vector3.zero;
            gameObject.SetActive(false);
        }
    }
}
