using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Status
{
    public class Fall : Physical
    {
        public Idle idle_;
        public override void Initialize()
        {
            idle_ = (Idle)Player_Controller.states_[0];
            state_ = Player_Controller.States.FALL;
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

        private void OnCollisionEnter2D(Collision2D collision)
        {
            if (controller_.current_State_ == Player_Controller.States.FALL)
                idle_.Enter();
        }
    }
}