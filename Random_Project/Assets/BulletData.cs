using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletData : ScriptableObject
{
    [SerializeField] public GameObject bullet_Template_;
    public float range_Normal_, range_Triple_, range_Split_;
    public float triple_Offset_, split_angle_;
    public Vector3 bullet_Speed_;
}
