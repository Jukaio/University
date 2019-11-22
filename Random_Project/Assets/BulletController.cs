using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletController : MonoBehaviour
{
    SingletonObjectStates state_Param_;
    public SingletonObjectStates.Bullet_Type bullet_Type_;
    PlayerController player_Controller_;

    public Vector3 bullet_Speed_;
    float range_;

    public void Set_Bullet_Type(SingletonObjectStates.Bullet_Type type)
    {
        bullet_Type_ = type;
    }

    void Start()
    {
        player_Controller_ = transform.parent.GetComponent<PlayerParent>().player_Parent.GetComponent<PlayerController>();
    }

    void OnEnable()
    {
        switch (transform.parent.GetComponent<PlayerParent>().player_Parent.GetComponent<PlayerController>().weapon_Type_)
        {
            case SingletonObjectStates.Weapon_Type.NORMAL:
                range_ = 20;
                break;

            case SingletonObjectStates.Weapon_Type.TRIPLE:
                range_ = 10;
                break;

            case SingletonObjectStates.Weapon_Type.TRIPLE_SPLIT:
                range_ = 10;
                break;
        }
    }

    // Update is called once per frame
    void Update()
    {
        switch(bullet_Type_)
        {
            case SingletonObjectStates.Bullet_Type.NORMAL:
                transform.position += bullet_Speed_;
                break;

            case SingletonObjectStates.Bullet_Type.TRIPLE:
                transform.position += bullet_Speed_;
                break;

            case SingletonObjectStates.Bullet_Type.TRIPLE_SPLIT_LEFT:
                //Rotate to the left (Rotation Matrix left * with Range)
                break;

            case SingletonObjectStates.Bullet_Type.TRIPLE_SPLIT_MIDDLE:
                transform.position += bullet_Speed_;
                break;

            case SingletonObjectStates.Bullet_Type.TRIPLE_SPLIT_RIGHT:
                //Rotate to the right (Rotation Matrix right * with Range)
                break;
        }

        if (transform.position.z >= range_)
        {
            gameObject.SetActive(false);
        }
    }
}
