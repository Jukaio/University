//Wyvern_Engine.cpp

#include "Input/Input_Handler.h"
#include "Wyvern_Engine.h"
#include "Time.h"
#include <SDL_Font/SDL_ttf.h>
#include "Renderer.h"
#include "Texture_Manager.h"

Wyvern_Engine::Wyvern_Engine()
{

}

void Wyvern_Engine::Initialise()
{
	Renderer::Initialise();
	Time::Initialise();
	Input_Handler::Initialise();
	Texture_Manager::Initialise();
	
	TTF_Init();

	game_.Initialise();

}

void Wyvern_Engine::Run()
{
	bool running = true;
	while (running)
	{
		Time::Update();
		if (!Input_Handler::Handle_Input_Events())
			running = false;

		game_.Update();
		game_.Render();
	}
}

void Wyvern_Engine::Exit()
{
	game_.Exit();

	TTF_Quit();

	Texture_Manager::Destroy();
	Input_Handler::Clean();
	Time::Clean();
	Renderer::Destroy();
	SDL_Quit();
}
