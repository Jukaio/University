using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Status
{
    public class Physical : State
    {
        public Rigidbody2D rigid_Body_2D_;

        public override void Initialize()
        {
            base.Initialize();
            rigid_Body_2D_ = GetAddComponent<Rigidbody2D>();
        }

        public override void Enter()
        {
            base.Enter();
        }

        public override void Handle_State(KeyValuePair<Button_Names, Input_Manager.Button_Data> button)
        {

        }

        public override void Stay()
        {
            base.Stay();
        }
    }
}