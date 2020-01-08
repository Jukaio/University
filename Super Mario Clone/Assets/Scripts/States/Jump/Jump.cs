using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Status
{
    public class Jump : Physical
    {
        public Fall fall_;

        public override void Initialize()
        {
            fall_ = (Fall)Player_Controller.states_[6];
            state_ = Player_Controller.States.JUMP;
            base.Initialize();
        }

        public override void Enter()
        {
            base.Enter();
            rigid_Body_2D_.AddForce(Vector2.up * 100.0f);
        }

        public override void Handle_State(KeyValuePair<Button_Names, Input_Manager.Button_Data> button)
        {
            if (rigid_Body_2D_.velocity.y < 0)
                fall_.Enter();

            switch (button.Key)
            {
                case Button_Names.MOVE_LEFT:
                    switch (button.Value.state_)
                    {
                        case Button_State.PRESSED:
                            break;
                        case Button_State.RELEASED:
                            break;
                    }
                    break;

                case Button_Names.MOVE_RIGHT:
                    switch (button.Value.state_)
                    {
                        case Button_State.PRESSED:
                            break;
                        case Button_State.RELEASED:
                            break;
                    }
                    break;
            }
            //rigid_Body_2D_.velocity = new Vector2(0.0f, rigid_Body_2D_.velocity.y);
        }

        public override void Stay()
        {
            base.Stay();
        }
    }
}