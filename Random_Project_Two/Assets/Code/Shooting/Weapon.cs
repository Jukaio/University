using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using Key = Custom_Input.Key;

namespace Weapons
{
    public class Weapon
    {
        enum Shooting_State
        {
            CAN_SHOOT,
            SHOOTING,
            COOLDOWN,
        }
        Shooting_State current_Shoot_State_;

        Key slot_Key_;
        bool shoot_Pressed_ = false;
        float cooldown_;
        float max_Cooldown_;

        AudioSource audio_Source_;
        Weapon_Component[] weapon_Components_ = new Weapon_Component[0];

        public bool Compare_Slot_Key(Key key)
        {
            return key == slot_Key_;
        }

        public Weapon(float cooldown, AudioSource audio_Source, AudioClip audio_Clip)
        {
            max_Cooldown_ = cooldown;
            audio_Source_ = audio_Source;

            audio_Source.clip = audio_Clip;
        }


        public void Add_Weapon_Component(Weapon_Component component)
        {

            if (weapon_Components_.Length == 0)
                weapon_Components_ = new Weapon_Component[1];
            else
            {
                Weapon_Component[] temp_List_ = weapon_Components_;
                weapon_Components_ = new Weapon_Component[temp_List_.Length + 1];
                for (int i = 0; i < temp_List_.Length; i++)
                {
                    weapon_Components_[i] = temp_List_[i];
                }
            }
            weapon_Components_[weapon_Components_.Length - 1] = component;
        }

        public void Push_Shoot()
        {
            shoot_Pressed_ = true;
        }

        public void Handle_State()
        {
            switch (current_Shoot_State_)
            {
                case Shooting_State.CAN_SHOOT:
                    if (shoot_Pressed_)
                        goto case Shooting_State.SHOOTING;
                    break;

                case Shooting_State.SHOOTING:
                    audio_Source_.Play();
                    Shooting();
                    break;

                case Shooting_State.COOLDOWN:
                    Cooldown();
                    break;
            }
        }

        void Shooting()
        {
            foreach (Weapon_Component component in weapon_Components_)
            {
                component.Prepare_Shooting();
            }
            cooldown_ = max_Cooldown_;
            current_Shoot_State_ = Shooting_State.COOLDOWN;
        }

        void Cooldown()
        {
            cooldown_ -= Time.deltaTime;
            if (cooldown_ < 0)
            {
                current_Shoot_State_ = Shooting_State.CAN_SHOOT;
            }
        }

        public void Clear()
        {
            shoot_Pressed_ = false;
        }
    }
}
