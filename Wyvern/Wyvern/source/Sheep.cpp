// Sheep.cpp

#include "Sheep.h"
#include "Wyvern_Game.h"
#include "Components/Transform_Component.h"
#include "Components/Render_Component.h"
#include "Components/AI_Sheep_Component.h"

Sheep::Sheep(Wyvern_Game* game)
{
	Set_Active(true);
	// Set Grid
	grid_ = game->Get_Grid();

	// Basic Transform
	transform_ = Add_Component<Transform_Component>();

	// Render and set Texture
	render_ = Add_Component<Render_Component, Transform_Component, Camera>(transform_, game->Get_Camera());
	render_->Set_Texture("Sprite_Sheet");

	// Set Transform Variables
	transform_->Set_Origin(Vector2(8, 8));
	transform_->Set_Size(Vector2(64, 64));

	// Set Render Rectangles
	render_->Set_Src_Rect(SDL_Rect({ 0, 32, 32, 32 }));
	render_->Set_Dst_Rect(SDL_Rect({ 0, 0, 32, 32 }));

	// AI
	ai_ = new AI_Sheep_Component(this, 0.0f, 0.0f, 0.0f, game);
	Add_Component(ai_);
}

Sheep::~Sheep()
{
	Clear_Components();
	ai_ = nullptr;
	transform_ = nullptr;
	render_ = nullptr;
	grid_ = nullptr;
}

void Sheep::Update()
{
	ai_->Update();
}

void Sheep::Render()
{
	render_->Render_Frame();
}

void Sheep::Enable()
{
	Set_Active(true);
	ai_->On_Enable();
}

void Sheep::Disable()
{
	Set_Active(false);
	ai_->On_Disable();
}

Grid* Sheep::Get_Grid()
{
	return grid_;
}

Transform_Component* Sheep::Get_Transform()
{
	return transform_;
}

Render_Component* Sheep::Get_Render()
{
	return render_;
}

