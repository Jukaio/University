// Wyvern_Game.cpp

#include "Wyvern_Game.h"
#include "Renderer.h"
#include "Game_Object.h"
#include <iostream>
#include "Texture_Manager.h"
#include <SDL2/SDL.h>

Wyvern_Game::Wyvern_Game()
{
	
}

void Wyvern_Game::Initialise()
{
	Texture_Manager::Add("test", "assets/sword.jpg");
	Texture_Manager::Get("test");
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
