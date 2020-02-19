// Wyvern_Game.cpp

#include "Wyvern_Game.h"
#include "Renderer.h"
#include "Player.h"

Wyvern_Game::Wyvern_Game()
{

}

void Wyvern_Game::Initialise()
{
	Player* player = new Player(Vector2(100, 100), Vector2(100, 100), Vector2(0.5f, 0.5f), &world_);
	Game_Object* game_Obj = new Game_Object(Vector2(50, 50), Vector2(50, 50), Vector2(0.5f, 0.5f));
	world_.Set_Player(player);
	world_.Add(game_Obj);
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
