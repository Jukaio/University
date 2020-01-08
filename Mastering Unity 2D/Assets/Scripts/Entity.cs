using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Entity : ScriptableObject
{
    public string name_;
    public int age_;
    string faction_;
    public string occupation_;
    public int level_ = 1;
    public int health_ = 2;
    public int strength_ = 1;
    public int magic_ = 0;
    public int defense_ = 0;
    public int speed_ = 1;
    public int damage_ = 1;
    public int armor_ = 0;
    public int no_Of_Attacks_ = 1;
    public string weapon_;
    public Vector2 position_;

    public void Take_Damage(int amount)
    {
        health_ -= Mathf.Clamp((amount - armor_), 0, int.MaxValue);
    }

    public void Attack(Entity other)
    {
        other.Take_Damage(strength_);
    }

    
}
