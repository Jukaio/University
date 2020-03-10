// Wyvern_Game.cpp

#include "Wyvern_Game.h"
#include "Game_Object.h"
#include <iostream>
#include "Engine/Texture_Manager.h"
#include <SDL2/SDL.h>
#include "Camera.h"
#include "Service.h"
#include "Engine/SDL_Pipeline.h"

Wyvern_Game::Wyvern_Game()
	: world_(nullptr)
	, camera_(nullptr)
{

}

void Wyvern_Game::Enter()
{
	Create_Interface();
	Create_World();
}


void Wyvern_Game::Create_Interface()
{
	camera_ = new Camera();
}

void Wyvern_Game::Create_World()
{
	Service<Texture_Manager>::Get()->Add("Test_Animation", "assets/Test_Animation.png");
	world_ = new World(this);
}

void Wyvern_Game::Update()
{
	world_->Update();
}

void Wyvern_Game::Render()
{
	SDL_RenderClear(Service<SDL_Pipeline>::Get()->Get_Renderer());

	world_->Render();

	SDL_SetRenderDrawColor(Service<SDL_Pipeline>::Get()->Get_Renderer(), 255, 255, 255, 255);
	SDL_RenderPresent(Service<SDL_Pipeline>::Get()->Get_Renderer());
}

void Wyvern_Game::Exit()
{
	delete world_;
	delete camera_;
}

Camera* Wyvern_Game::Get_Camera()
{
	return camera_;
}
