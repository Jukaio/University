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

	Get_Component<Transform_Component>()->Set_Size(Vector2(64, 64));
	Get_Component<Transform_Component>()->Set_Origin(Vector2(32, 32));

	Get_Component<Render_Component>()->Set_Texture_ID("Test_Animation");
	Get_Component<Render_Component>()->Set_Src_Rect(SDL_Rect({ 64, 0, 64, 64 }));
	Get_Component<Render_Component>()->Set_Dst_Rect(SDL_Rect({ 0, 0, 64, 64 }));
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
	Get_Component<Render_Component>()->Render_Frame();
}
