using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Status
{
    public class Fall_Right : Physical
    {
        public Movement_Right move_Right_;
        public Jump jump_;

        public override void Initialize()
        {
            state_ = Player_Controller.States.FALL_RIGHT;
            move_Right_ = (Movement_Right)Player_Controller.states_[2];
            jump_ = (Jump)Player_Controller.states_[3];
            base.Initialize();
        }

        public override void Enter()
        {
            base.Enter();
        }

        public override void Handle_State(KeyValuePair<Button_Names, Input_Manager.Button_Data> button)
        {
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
                            move_Right_.Translate_Right(2.0f, 10.0f);
                            break;
                        case Button_State.RELEASED:
                            jump_.Enter();
                            break;
                    }
                    break;
            }
        }

        public override void Stay()
        {
            base.Stay();
        }
    }
}