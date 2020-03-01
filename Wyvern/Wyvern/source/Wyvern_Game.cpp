// Wyvern_Game.cpp

#include "Wyvern_Game.h"
#include "Renderer.h"
#include "Game_Object.h"
#include <iostream>
#include "Components/Transform.h"

Wyvern_Game::Wyvern_Game()
{

}

void Wyvern_Game::Initialise()
{

}

void Wyvern_Game::Update()
{
	world_.Update();


}

void Wyvern_Game::Render()
{
	SDL_RenderClear(Renderer::Get_Renderer());

	world_.Render();


	SDL_SetRenderDrawColor(Renderer::Get_Renderer(), 255, 255, 255, 255);
	SDL_RenderPresent(Renderer::Get_Renderer());
}

void Wyvern_Game::Exit()
{

}
