using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Status
{
    public class Movement_Right : Movement
    {
        public Idle idle_;
        public override void Initialize()
        {
            state_ = Player_Controller.States.MOVEMENT_RIGHT;
            idle_ = (Idle) Player_Controller.states_[0];
            base.Initialize();
        }

        public override void Enter()
        {
            controller_.Change_State(Player_Controller.States.MOVEMENT_RIGHT, false);
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
                            Translate_Right(10.0f, 40.0f);
                            break;

                        case Button_State.RELEASED:
                            idle_.Enter();
                            rigid_Body_2D_.velocity = Vector2.zero;
                            break;
                    }
                    break;

                case Button_Names.JUMP:
                    switch (button.Value.state_)
                    {
                        case Button_State.PRESSED:
                            break;

                        case Button_State.RELEASED:

                            break;
                    }
                    break;

            }
        }

        public void Translate_Right(float speed, float max_Speed)
        {
            if (rigid_Body_2D_.velocity.x * Vector2.right.x < max_Speed)
                rigid_Body_2D_.velocity += speed * Vector2.right;
        }

        public override void Stay()
        {
            base.Stay();
        }
    }
}
