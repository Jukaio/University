// Grass.cpp

#include "Grass.h"
#include "Wyvern_Game.h"
#include "Components/Transform_Component.h"
#include "Components/Render_Component.h"
#include "Components/AI_Grass_Component.h"


Grass* Grass::Alloc_Grass(std::size_t size)
{
	void* raw_memory = operator new[](Grid::HEIGHT_GRID * Grid::WIDTH_GRID * sizeof(Grass));
	return (Grass*) raw_memory;
}

void Grass::Dealloc_Grass(Grass*& block, std::size_t size)
{
	for (Grass* ptr = block; ptr < &block[size]; ptr++)
		ptr->~Grass();
	operator delete[](block);
	block = nullptr;
}

Grass::Grass(Wyvern_Game* game, Vector2 pos)
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
	transform_->Set_Size(Vector2(64, 64));

	// Set Render Rectangles
	render_->Set_Src_Rect(SDL_Rect({ 0, 0, 32, 32 }));
	render_->Set_Dst_Rect(SDL_Rect({ 0, 0, 32, 32 }));

	// AI
	ai_ = new AI_Grass_Component(this, 0.0f, 0.0f, 0.0f, game);
	Add_Component(ai_);
}

Grass::~Grass()
{
	Clear_Components();
	ai_ = nullptr;
	transform_ = nullptr;
	render_ = nullptr;
	grid_ = nullptr;
}

void Grass::Update()
{
	Grass* temp = this;


	ai_->Update();
}

void Grass::Render()
{
	render_->Render_Frame();
}

void Grass::Enable()
{
	Set_Active(true);
	ai_->On_Enable();
}

void Grass::Disable()
{
	Set_Active(false);
	ai_->On_Disable();
}

Grid* Grass::Get_Grid()
{
	return grid_;
}

Transform_Component* Grass::Get_Transform()
{
	return transform_;
}

Render_Component* Grass::Get_Render()
{
	return render_;
}



