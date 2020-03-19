//Wyvern_Engine.cpp

#include "Input/Input_Handler.h"
#include "Wyvern_Engine.h"
#include "Time.h"
#include <SDL_Font/SDL_ttf.h>
#include "Engine/Texture_Manager.h"
#include "Service.h"
#include "Engine/SDL_Pipeline.h"
#include <iostream>

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
	const int FPS = 60;
	const int DELAY = 1000 / 60;

	int start = 0;
	int delta = 0;

	bool running = true;
	while (running)
	{
		Service<Time>::Get()->Update();
		start = Service<Time>::Get()->Run_Time().As_Miliseconds();
		if (!Service<Input_Handler>::Get()->Handle_Input_Events())
			running = false;

		game_.Update();
		game_.Render();
	

		delta = Service<Time>::Get()->Run_Time().As_Miliseconds() - start;
		std::cout << 1000 / Service<Time>::Get()->Delta_Time().As_Miliseconds() << "\n";
		if (DELAY > delta)
			SDL_Delay(DELAY - delta);
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
