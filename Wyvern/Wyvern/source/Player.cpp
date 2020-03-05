// Player.cpp

#include "Player.h"
#include "Components/Transform_Component.h"
#include "Components/Render_Component.h"
#include "Components/Input_Component.h"
#include "Wyvern_Game.h"

Player::Player(Wyvern_Game* game)
	: game_(game)
{
	// Basic Transform
	Add_Component<Transform_Component>();

	// Render
	Add_Component<Render_Component>();
	Get_Component<Render_Component>()->Set_Camera(game_->Get_Camera());

	// Input
	Add_Component<Input_Component>();


	///////// SET SET ////////
	Get_Component<Transform_Component>()->Set_Size(Vector2(64, 64));
	Get_Component<Transform_Component>()->Set_Origin(Vector2(32, 32));

	Get_Component<Render_Component>()->Set_Texture_ID("Test_Animation");
	Get_Component<Render_Component>()->Set_Src_Rect(SDL_Rect({ 64, 0, 64, 64 }));
	Get_Component<Render_Component>()->Set_Dst_Rect(SDL_Rect({ 0, 0, 64, 64 }));
}

Player::~Player()
{
	Clear_Components();
}

void Player::Update()
{
	Get_Component<Input_Component>()->Update();
}

void Player::Render()
{
	Get_Component<Render_Component>()->Render_Frame();
}
