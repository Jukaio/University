using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using Key = Custom_Input.Key;

namespace Weapons
{
    public class Weapon_Component
    {
        
        GameObject game_Object_;
        GameObject[] clip_ = new GameObject[0];
        int clip_Index_;
        float range_;
        Vector3 offset_;
        float bullet_Speed_;
        Vector3 direction_; //Unit Vector
        Vector3 angles_;

        public Weapon_Component(GameObject game_Object, GameObject clip_Object_Template, int clip_Size,
                      Vector3 angles, float range, Vector3 offset, float bullet_Speed, Vector3 direction)
        {
            game_Object_ = game_Object;
            range_ = range;
            offset_ = offset;
            angles_ = angles;
            bullet_Speed_ = bullet_Speed;
            direction_ = direction;

            Init_Bullet_Clip(clip_Size, clip_Object_Template);
        }
        private void Init_Bullet_Clip(int clip_Size, GameObject template)
        {
            template.SetActive(false);
            clip_ = new GameObject[clip_Size];
            for (int i = 0; i < clip_Size; i++)
            {
                clip_[i] = Object.Instantiate<GameObject>(template);
            }

        }


        public void Prepare_Shooting()
        {
            if (Inactive_Bullet_Count() >= 1)
            {
                Shooting(offset_, angles_, range_, direction_ * bullet_Speed_);
            }
            else //This way we can have endless shooting!
            {
                GameObject temp = Object.Instantiate<GameObject>(clip_[0]);
                temp.SetActive(false);
                //clip_.Add(temp);
                Prepare_Shooting();
            }
        }

        private void Shooting(Vector3 origin_modifier, Vector3 angles, float range, Vector3 bullet_Speed)
        {
            for (int i = 0; ; i++)
            {
                clip_Index_++;
                if (clip_Index_ >= clip_.Length)
                    clip_Index_ = 0;

                if (clip_[clip_Index_].activeSelf == false)
                {
                    Vector3 origin = new Vector3(game_Object_.transform.position.x + origin_modifier.x,
                                                 game_Object_.transform.position.y + origin_modifier.y,
                                                 game_Object_.transform.position.z + origin_modifier.z);

                    clip_[clip_Index_].GetComponent<Bullet_Controller>().Activate_Bullet(origin, bullet_Speed, angles, range);
                    return;
                }

                if (i >= clip_.Length - 1)
                {
                    break;
                }
            }
        }

        private int Inactive_Bullet_Count()
        {
            int count = 0;
            for (int i = 0; i < clip_.Length; i++)
            {
                if (clip_[i].activeSelf == false)
                    count++;
            }
            return count;
        }
 
    }
}
