// Wyvern_Game.cpp

#include "Wyvern_Game.h"
#include "Game_Object.h"
#include <iostream>
#include "Engine/Texture_Manager.h"
#include <SDL2/SDL.h>
#include "Camera.h"
#include "Service.h"
#include "Engine/SDL_Pipeline.h"
#include "Mouse.h"
#include "Time.h"
Wyvern_Game::Wyvern_Game()
	: world_(nullptr)
	, camera_(nullptr)
	, grid_(nullptr)
{

}

void Wyvern_Game::Enter()
{
	Service<Texture_Manager>::Get()->Add("Sprite_Sheet", "assets/Sprite_Sheet.png");

	camera_ = new Camera();

	grid_ = new Grid();
	world_ = new World(this);

	//grid_->Get_Node(Vector2(5, 5))->Start_Set_Distance();
}


void Wyvern_Game::Update()
{
	world_->Update();


	Vector2 mouse_pos_to_grid = Grid::Global_To_Grid(Vector2((int)Service<Mouse>::Get()->Get_Mouse_Position().x_,
										(int)Service<Mouse>::Get()->Get_Mouse_Position().y_ ));
	//if (grid_->Get_Node(mouse_pos_to_grid)->has_Wolf_ == true)
	//	std::cout << "x: " << (int) (mouse_pos_to_grid.x_) << " y: " << (int)(mouse_pos_to_grid.y_) << ": " << "I AM TRUE\n";
	//else
	//std::cout << "x: " << (int) (mouse_pos_to_grid.x_) << " y: " << (int) (mouse_pos_to_grid.y_) << "  " << grid_->Get_Node(mouse_pos_to_grid)->distance_ << "\n";

}

void Wyvern_Game::Render()
{
	SDL_RenderClear(Service<SDL_Pipeline>::Get()->Get_Renderer()); 
	

	SDL_Rect src_Rect{ 0, 0, 32, 32 };
	SDL_Rect render_dst_Rect_{ 0, 0, Settings::WIDTH, Settings::HEIGHT };
	SDL_RenderCopyEx(Service<SDL_Pipeline>::Get()->Get_Renderer(), Service<Texture_Manager>::Get()->Get("Sprite_Sheet")->texture_, &src_Rect, &render_dst_Rect_, 0, 0, SDL_FLIP_NONE);

	world_->Render();	
	grid_->Render_Nodes();

	SDL_SetRenderDrawColor(Service<SDL_Pipeline>::Get()->Get_Renderer(), 255, 255, 255, 255);
	SDL_RenderPresent(Service<SDL_Pipeline>::Get()->Get_Renderer());
}

void Wyvern_Game::Exit()
{
	delete world_;
	delete grid_;
	delete camera_;
}

World* Wyvern_Game::Get_World()
{
	return world_;
}

Camera* Wyvern_Game::Get_Camera()
{
	return camera_;
}

Grid* Wyvern_Game::Get_Grid()
{
	return grid_;
}
