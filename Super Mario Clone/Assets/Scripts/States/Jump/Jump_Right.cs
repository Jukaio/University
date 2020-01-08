using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Status
{
    public class Jump_Right : Physical
    {
        public override void Initialize()
        {
            state_ = Player_Controller.States.JUMP_RIGHT;
            base.Initialize();
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