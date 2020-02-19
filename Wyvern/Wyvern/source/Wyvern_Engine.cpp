//Wyvern_Engine.cpp

#include "Wyvern_Engine.h"
#include "Time.h"
#include <SDL_Font/SDL_ttf.h>
#include "Renderer.h"


Wyvern_Engine::Wyvern_Engine()
{

}

void Wyvern_Engine::Initialise()
{
	Renderer::Initialise();
	Time::Initialise();
	input_Handler_.Initialise();
	TTF_Init();

	game_.Initialise();

}

void Wyvern_Engine::Run()
{
	bool running = true;
	while (running)
	{
		Time::Update();
		if (!input_Handler_.Handle_Input_Events())
			running = false;

		game_.Update();
		game_.Render();
	}
}

void Wyvern_Engine::Exit()
{
	game_.Exit();
	TTF_Quit();
	Time::Clean();
	Renderer::Destroy();
	SDL_Quit();
}
