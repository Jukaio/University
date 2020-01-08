using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Status
{
    public class State : MonoBehaviour
    {
        public Player_Controller controller_;
        public System.Type state_Type_;
        public Player_Controller.States state_;
        public int clip_ID_;

        public virtual void Initialize()
        {
            controller_ = GetAddComponent<Player_Controller>();
            clip_ID_ = (int)state_;
        }

        public virtual void Enter()
        {
            controller_.Change_State(state_);
        }

        public virtual void Handle_State(KeyValuePair<Button_Names, Input_Manager.Button_Data> button)
        {

        }

        public virtual void Stay()
        {

        }

        public T GetAddComponent<T>()
        {
            T component;
            if (GetComponent<T>() == null)
            {
                gameObject.AddComponent(typeof(T));
                Debug.LogError("ADDED " + GetComponent<T>().GetType() + " COMPONENT\nPlease Add Component to the Inspector");
            }
            component = GetComponent<T>();
            return component;
        }
    }
}