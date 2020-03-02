// Player.cpp

#include "Player.h"
#include "Components/Transform_Component.h"
#include "Components/Render_Component.h"
#include "Components/Input_Component.h"

Player::Player()
{
	Add_Component<Transform_Component>();
	Add_Component<Render_Component>();
	Add_Component<Input_Component>();

	Get_Component<Transform_Component>()->Set_Size(Vector2(160, 160));
}

Player::~Player()
{

}

void Player::Update()
{
	Get_Component<Input_Component>()->Update();
}

void Player::Render()
{
	Get_Component<Render_Component>()->Render_Frame("test");
}
