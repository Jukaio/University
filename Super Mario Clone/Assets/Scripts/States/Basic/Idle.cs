using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Status
{
    public class Idle : Physical
    {
        public Movement_Left move_Left_;
        public Movement_Right move_Right_;
        public Jump jump_;

        public override void Initialize()
        {
            move_Left_ = (Movement_Left)Player_Controller.states_[1];
            move_Right_ = (Movement_Right)Player_Controller.states_[2];
            jump_ = (Jump)Player_Controller.states_[3];
            state_ = Player_Controller.States.IDLE;
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
                            move_Left_.Enter();
                            break;

                        case Button_State.RELEASED:

                            break;
                    }
                    break;

                case Button_Names.MOVE_RIGHT:
                    switch (button.Value.state_)
                    {
                        case Button_State.PRESSED:
                            move_Right_.Enter();
                            break;

                        case Button_State.RELEASED:

                            break;
                    }
                    break;

                case Button_Names.JUMP:
                    switch (button.Value.state_)
                    {
                        case Button_State.PRESSED:
                            jump_.Enter();
                            break;

                        case Button_State.RELEASED:

                            break;
                    }
                    break;

            }
        }

        public override void Stay()
        {
            rigid_Body_2D_.velocity = Vector2.zero;
            base.Stay();
        }
    }
}