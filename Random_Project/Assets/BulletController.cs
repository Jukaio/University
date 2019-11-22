using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletController : MonoBehaviour
{
    SingletonObjectStates state_Param_;
    public SingletonObjectStates.Bullet_Type bullet_Type_;
    PlayerController player_Controller_;

    public Vector3 bullet_Speed_;
    float range;

    void Start()
    {
        player_Controller_ = transform.parent.GetComponent<PlayerParent>().player_Parent.GetComponent<PlayerController>();
    }

    void OnEnable()
    {
        switch(transform.parent.GetComponent<PlayerParent>().player_Parent.GetComponent<PlayerController>().weapon_Type_)
        {
            case SingletonObjectStates.Weapon_Type.NORMAL:
                bullet_Type_ = SingletonObjectStates.Bullet_Type.NORMAL;
                range = 20;
                break;

            case SingletonObjectStates.Weapon_Type.TRIPLE:
                bullet_Type_ = SingletonObjectStates.Bullet_Type.TRIPLE;
                range = 10;
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
        }

        if (transform.position.z >= range)
        {
            gameObject.SetActive(false);
            transform.position = player_Controller_.transform.position;
        }
    }
}
