//InputHandler.cpp

#include "Input/Input_Handler.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include <SDL2/SDL.h>
#include "Service.h"


Input_Handler::Input_Handler()
{
	Service<Keyboard>::Set(new Keyboard());
	Service<Mouse>::Set(new Mouse());
}

Input_Handler::~Input_Handler()
{
	Service<Keyboard>::Clean();
	Service<Mouse>::Clean();

	SDL_FlushEvents(0, SDL_LASTEVENT);
}

bool Input_Handler::Handle_Input_Events()
{
	Service<Keyboard>::Get()->Update_Last_Frame();
	Get_Mouse_Position();

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:		return false;
			case SDL_KEYDOWN:	Service<Keyboard>::Get()->Update_Key(event.key.keysym.scancode, true);	break;
			case SDL_KEYUP:		Service<Keyboard>::Get()->Update_Key(event.key.keysym.scancode, false); break;
		}
	}
	return true;
}

void Input_Handler::Get_Mouse_Position()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	Service<Mouse>::Get()->Set_Mouse_Position(x, y);
}

