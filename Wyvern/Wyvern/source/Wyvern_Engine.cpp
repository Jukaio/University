//Wyvern_Engine.cpp

#include "Input/Input_Handler.h"
#include "Wyvern_Engine.h"
#include "Time.h"
#include <SDL_Font/SDL_ttf.h>
#include "Engine/Texture_Manager.h"
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
	Service<Input_Handler>::Set(new Input_Handler());
	Service<Texture_Manager>::Set(new Texture_Manager());
	

	game_.Enter();

}

void Wyvern_Engine::Run()
{
	bool running = true;
	while (running)
	{
		Service<Time>::Get()->Update();
		if (!Service<Input_Handler>::Get()->Handle_Input_Events())
			running = false;

		game_.Update();
		game_.Render();
		
		// FIX FPS!
		if (1000 / 60 > Service<Time>::Get()->Get_Delta_Time().As_Miliseconds())
			SDL_Delay((1000 / 60) - Service<Time>::Get()->Get_Delta_Time().As_Miliseconds());
	}
}

void Wyvern_Engine::Exit()
{
	game_.Exit();

	Service<Texture_Manager>::Clean();
	Service<Input_Handler>::Clean();
	Service<Time>::Clean();
	Service<SDL_Pipeline>::Clean();
	
	SDL_Quit();
}
