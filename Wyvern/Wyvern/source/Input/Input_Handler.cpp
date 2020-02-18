//InputHandler.cpp

#include "Input/Input_Handler.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include <SDL2/SDL.h>

Input_Handler::Input_Handler()
{

}

Input_Handler::~Input_Handler()
{
	Keyboard::Clean();
	Mouse::Clean();
}

void Input_Handler::Initialise()
{
	Keyboard::Initialise();
	Mouse::Initialise();
}

bool Input_Handler::Handle_Input_Events()
{
	Keyboard::Update();
	Get_Mouse_Position();

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:		return false;
			case SDL_KEYDOWN:	Keyboard::Update_Key(event.key.keysym.scancode, true);	break;
			case SDL_KEYUP:		Keyboard::Update_Key(event.key.keysym.scancode, false); break;
		}
	}
	return true;
}

void Input_Handler::Get_Mouse_Position()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	Mouse::Set_Mouse_Position(x, y);
}

