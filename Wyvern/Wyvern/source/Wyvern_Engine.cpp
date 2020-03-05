//Wyvern_Engine.cpp

#include "Input/Input_Handler.h"
#include "Wyvern_Engine.h"
#include "Time.h"
#include <SDL_Font/SDL_ttf.h>
#include "Texture_Manager.h"
#include "Service.h"
#include "Engine/SDL_Pipeline.h"

Wyvern_Engine::Wyvern_Engine()
{

}

// Finish the Service System for Input and Texture Manager
void Wyvern_Engine::Initialise()
{
	Service<SDL_Pipeline>::Set(new SDL_Pipeline());
	Service<Time>::Set(new Time());
	Input_Handler::Initialise();
	Texture_Manager::Initialise();
	

	game_.Initialise();

}

void Wyvern_Engine::Run()
{
	bool running = true;
	while (running)
	{
		Service<Time>::Get()->Update();
		if (!Input_Handler::Handle_Input_Events())
			running = false;

		game_.Update();
		game_.Render();
	}
}

void Wyvern_Engine::Exit()
{
	game_.Exit();


	Texture_Manager::Destroy();
	Input_Handler::Clean();
	Service<Time>::Clean();
	Service<SDL_Pipeline>::Clean();
	
	SDL_Quit();
}
