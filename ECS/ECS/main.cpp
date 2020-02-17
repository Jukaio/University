//main.cpp

#include <SDL.h>
#include "main.h"

typedef unsigned int uint32_t;


struct IEntity
{
	IEntity();
	virtual ~IEntity();

};

struct Entity
{

};

struct Component
{

};

struct Entity_Manager
{
	Entity* entities_;
};

struct Component_Manager
{

};

struct System_Manager
{

};

int main(int argc, char* args[])
{
	SDL_Window* window = SDL_CreateWindow("ECS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, 0);
	SDL_Event event;

	bool running = true;
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					running = false;
					break;
			}
		}

		
	}

	return 0;
}