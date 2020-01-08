using System.Collections.Generic;
using UnityEngine;

using Key = Custom_Input.Key;

namespace Weapons
{
    public class Weapon_Manager
    {
        public GameObject game_Object_;
        List<Weapon_Component> weapon_Components = new List<Weapon_Component>();
        Weapon[] weapons_ = new Weapon[0];
        AudioSource audio_Source_;
        AudioClip[] audio_Clips_;
        int current_Slot_ = 0;
        float Weapon_Change_Cooldown_;

        public Weapon_Manager(GameObject game_Object, AudioSource audio_Source, AudioClip[] audio_Clips)
        {
            game_Object_ = game_Object;
            audio_Source_ = audio_Source;
            audio_Clips_ = audio_Clips;
        }

        public void Create_Weapon_Component(GameObject clip_Object_Template, int clip_Size, Vector3 angles, float range,
                             Vector3 offset, float bullet_Speed, Vector3 direction)
        {
            Weapon_Component temp = new Weapon_Component(game_Object_, clip_Object_Template, clip_Size, angles, range, offset, bullet_Speed, direction);
            weapon_Components.Add(temp);
            MonoBehaviour.print("ADDED COMPONENT");
        }

        public void Create_Weapon(Key shoot_Key, float cooldown)
        {
            Weapon temp_Weapon = new Weapon(cooldown, audio_Source_, audio_Clips_[0]);

            if (weapons_.Length == 0)
                weapons_ = new Weapon[1];
            else
            {
                Weapon[] temp_List_ = weapons_;
                weapons_ = new Weapon[temp_List_.Length + 1];
                for (int i = 0; i < temp_List_.Length; i++)
                {
                    weapons_[i] = temp_List_[i];
                }
            }
            weapons_[weapons_.Length - 1] = temp_Weapon;
            MonoBehaviour.print("Created Weapon");
        }

        public void Construct_Weapon(int slot_Index, int weapon_Index) //Add one to slot
        {
            weapons_[slot_Index].Add_Weapon_Component(weapon_Components[weapon_Index]);
        }

        public void Construct_Weapon(int slot_Index, int weapon_Index_from, int weapon_Index_to) //Add range to slot
        {
            for (int i = weapon_Index_from; i <= weapon_Index_to; i++)
            {
                weapons_[slot_Index].Add_Weapon_Component(weapon_Components[i]);

            }
        }

        public void Change_Weapon(int slot)
        {
            if (slot != current_Slot_)
            {
                current_Slot_ = slot;
                Weapon_Change_Cooldown_ = 1.0f;
            }
        }

        public void Push_Shoot_Weapon()
        {
            if (Weapon_Change_Cooldown_ > 0)
                return;

            weapons_[current_Slot_].Push_Shoot();
        }

        public void Handle_Weapon_Change_Cooldown()
        {
            if (Weapon_Change_Cooldown_ > 0)
                Weapon_Change_Cooldown_ -= Time.deltaTime;
            else if (Weapon_Change_Cooldown_ < 0)
                Weapon_Change_Cooldown_ = 0;
        }

        public void Handle_State()
        {
            foreach (Weapon weapon in weapons_)
            {
                weapon.Handle_State();
                weapon.Clear(); //Clear can happen directly after handling the States
            }
        }

        public void Clear()
        {
            foreach (Weapon weapon in weapons_)
            {
                weapon.Clear();
            }
        }
    }
}
